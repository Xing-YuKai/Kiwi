//
// Created by kiwi on 19-1-7.
//

#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"

thread_local Kiwi::EventLoop *_thread_local_event_loop_ = nullptr;

Kiwi::EventLoop::EventLoop() :
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

void Kiwi::EventLoop::loop()
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
		for (Channel* channel:_active_channels_)
		{
			channel->handle_event();
		}
	}
}

void Kiwi::EventLoop::stop()
{
	_stop_.store(true);
}

void Kiwi::EventLoop::add_channel(Channel *channel)
{
	assert_in_event_loop_thread();
	_epoll_ptr_->add_channel(channel);
}

void Kiwi::EventLoop::remove_channel(Channel *channel)
{
	assert_in_event_loop_thread();
	assert(channel->get_loop() == this);
	_epoll_ptr_->remove_channel(channel);
}

void Kiwi::EventLoop::update_channel(Channel *channel)
{
	assert_in_event_loop_thread();
	assert(channel->get_loop() == this);
	_epoll_ptr_->update_channel(channel);
}

void Kiwi::EventLoop::assert_in_event_loop_thread()
{
	if (_thread_id_ != std::this_thread::get_id())
	{
		std::cerr << "EventLoop assert_in_event_loop_thread error : " << "EventLoop thread "
				  << _thread_id_ << "is not this thread" << std::this_thread::get_id() << std::endl;
		std::terminate();
	}
}

Kiwi::EventLoop::~EventLoop()
{
	_thread_local_event_loop_ = nullptr;
}