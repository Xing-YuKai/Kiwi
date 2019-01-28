//
// Created by kiwi on 19-1-7.
//

#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"

using namespace Kiwi;
using namespace Kiwi::Type;

thread_local EventLoop *_thread_local_event_loop_ = nullptr;

EventLoop::EventLoop() :
		_looping_(false),
		_stop_(false),
		_thread_id_(std::this_thread::get_id()),
		_epoll_ptr_(new Epoll(this))
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
		_epoll_ptr_->poll(_active_channels_);
		for (Channel *channel:_active_channels_)
		{
			channel->handle_event();
		}
	}
}

void EventLoop::stop()
{
	_stop_.store(true);
}

void EventLoop::add_channel(Channel *channel)
{
	assert_in_event_loop_thread();
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
	_thread_local_event_loop_ = nullptr;
}

void EventLoop::run_in_loop(Functor functor)
{
	if (std::this_thread::get_id() == _thread_id_)
	{
		functor();
	} else
	{
		{
			std::lock_guard<std::mutex> lock_guard(_mutex_);
			_pending_functors_.emplace_back(std::move(functor));
		}
		if (_handling_functors_.load() || std::this_thread::get_id() != _thread_id_)
		{
			wakeup();
		}
	}
}

std::future<Type::TimerID> EventLoop::run_after(TimerHandler handler, TimeRange interval)
{
	auto functor_ptr = std::make_shared<std::packaged_task<Type::TimerID()>>(
			[this, handler, interval] -> TimerID { return this->_timer_pool_->start_timer(interval, handler); });

	std::future<Type::TimerID> res = functor_ptr->get_future();

	run_in_loop([functor_ptr] { (*functor_ptr)(); });

	return res;
}

void EventLoop::cancel_in_loop(std::future<TimerID> future)
{
	run_in_loop([this, future] { this->_timer_pool_->stop_timer(future.get()); });
}

void EventLoop::wakeup()
{
	
}

void EventLoop::handle_pending_functors()
{

}
