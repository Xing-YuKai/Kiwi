//
// Created by kiwi on 19-1-7.
//

#include <csignal>
#include <sys/eventfd.h>
#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"

using namespace Kiwi;
using namespace Kiwi::Type;

namespace
{
	thread_local EventLoop *_thread_local_event_loop_ = nullptr;

	int create_eventfd()
	{
		int fd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
		if (fd < 0)
		{
			std::cerr << "create_eventfd error : " << errno << strerror(errno) << std::endl;
			std::terminate();
		}
		return fd;
	}

	class IgnoreSIGPIPE
	{
	public:
		IgnoreSIGPIPE()
		{
			signal(SIGPIPE, SIG_IGN);
		}
	};

	IgnoreSIGPIPE obj;
}

EventLoop::EventLoop() :
		_looping_(false),
		_stop_(false),
		_handling_events_(false),
		_handling_functors_(false),
		_epoll_ptr_(new Epoll(this)),
		_timer_pool_ptr_(new TimerPool),
		_wakeup_channel_(new Channel(this, create_eventfd())),
		_thread_id_(std::this_thread::get_id())
{
	if (_thread_local_event_loop_)
	{
		std::cerr << "EventLoop construct error : " << _thread_local_event_loop_
				  << " exist in this thread " << std::this_thread::get_id() << std::endl;
		std::terminate();
	} else
	{
		_thread_local_event_loop_ = this;
	}
	ReadEventHandler handler = std::bind(&EventLoop::wakeup_read_handler, this);
	_wakeup_channel_->set_read_handler(handler);
	_wakeup_channel_->enable_reading();
	_wakeup_channel_->update();
}

void EventLoop::loop()
{
	if (_looping_.load())
	{
		std::cerr << "EventLoop loop error : " << "loop on a looping EventLoop" << std::endl;
		std::terminate();
	}
	assert_in_event_loop_thread();
	_looping_.store(true);

	while (!_stop_.load())
	{
		_active_channels_.clear();

		TimeRange ret_time = _epoll_ptr_->poll(_active_channels_, EPOLL_WAIT_TIME_OUT);
		_timer_pool_ptr_->update();

		_handling_events_.store(true);
		for (Channel *channel:_active_channels_)
		{
			channel->handle_event(ret_time);
		}
		_handling_events_.store(false);

		handle_pending_functors();
	}

	_looping_.store(false);
}

void EventLoop::stop()
{
	_stop_.store(true);
	if (std::this_thread::get_id() != _thread_id_)
		wakeup();
}

void EventLoop::add_channel(Channel *channel)
{
	assert_in_event_loop_thread();
	assert(channel->get_loop() == this);
	_epoll_ptr_->add_channel(channel);
}

void EventLoop::remove_channel(Channel *channel)
{
	assert_in_event_loop_thread();
	assert(channel->get_loop() == this);
	_epoll_ptr_->remove_channel(channel);
}

void EventLoop::update_channel(Channel *channel)
{
	assert_in_event_loop_thread();
	assert(channel->get_loop() == this);
	_epoll_ptr_->update_channel(channel);
}

bool EventLoop::has_channel(Channel *channel)
{
	assert_in_event_loop_thread();
	assert(channel->get_loop() == this);
	return _epoll_ptr_->has_channel(channel);
}

void EventLoop::run_in_loop(Functor functor)
{
	if (std::this_thread::get_id() == _thread_id_)
		functor();
	else
		queue_in_loop(functor);
}

void EventLoop::queue_in_loop(Type::Functor functor)
{
	{
		std::lock_guard<std::mutex> lock_guard(_mutex_);
		_pending_functors_.emplace_back(functor);
	}
	if (_handling_functors_.load() || std::this_thread::get_id() != _thread_id_)
	{
		wakeup();
	}
}

std::future<Type::TimerID> EventLoop::run_after(TimerHandler handler, TimeRange interval)
{
	auto functor_ptr = std::make_shared<std::packaged_task<Type::TimerID()>>(
			[this, handler, interval]() -> TimerID { return this->_timer_pool_ptr_->start_timer(interval, handler); });

	std::future<Type::TimerID> res = functor_ptr->get_future();

	run_in_loop([functor_ptr] { (*functor_ptr)(); });

	return res;
}

void EventLoop::cancel_in_loop(std::future<TimerID> future)
{
	run_in_loop([this, &future]
				{
					TimerID id = future.get();
					this->_timer_pool_ptr_->stop_timer(id);
				});
}

void EventLoop::wakeup()
{
	uint64_t one = 1;
	ssize_t n = write(_wakeup_channel_->get_fd(), &one, sizeof(one));
	if (n != sizeof(one))
	{
		std::cerr << "wakeup error : write " << n << "bytes instead of " << sizeof(one) << std::endl;
		std::terminate();
	}
}

void EventLoop::handle_pending_functors()
{
	std::vector<Functor> functors;
	_handling_functors_.store(true);

	{
		std::lock_guard<std::mutex> lock_guard(_mutex_);
		functors.swap(_pending_functors_);
	}
	for (const auto &functor:functors)
		functor();

	_handling_functors_.store(false);
}

void EventLoop::assert_in_event_loop_thread()
{
	if (_thread_id_ != std::this_thread::get_id())
	{
		std::cerr << "EventLoop assert_in_event_loop_thread error : " << "EventLoop thread "
				  << _thread_id_ << "is not this thread" << std::this_thread::get_id() << std::endl;
		std::terminate();
	}
}

EventLoop::~EventLoop()
{
	_wakeup_channel_->disable_all();
	_wakeup_channel_->remove();
	close(_wakeup_channel_->get_fd());
	_thread_local_event_loop_ = nullptr;
}

void EventLoop::wakeup_read_handler()
{
	uint64_t one = 1;
	ssize_t n = read(_wakeup_channel_->get_fd(), &one, sizeof(one));
	if (n != sizeof(one))
	{
		std::cerr << "wakeup error : write " << n << "bytes instead of " << sizeof(one) << std::endl;
		std::terminate();
	}
}