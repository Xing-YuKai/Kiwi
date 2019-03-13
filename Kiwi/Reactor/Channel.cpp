//
// Created by kiwi on 19-1-7.
//

#include "Channel.h"

using namespace Kiwi;
using namespace Kiwi::Type;

Channel::Channel(EventLoop *event_loop, int fd) :
		_owner_event_loop_(event_loop),
		_fd_(fd),
		_events_(0),
		_revents_(0),
		_in_loop_(false),
		_handling_event_(false) {}


void Channel::handle_event(TimeRange receive_time)
{
	_handling_event_ = true;

	if ((_revents_ & EPOLLHUP) && !(_revents_ & EPOLLIN))
		if (_close_handler_)
			_close_handler_();
	if (_revents_ & EPOLLERR)
		if (_error_handler_)
			_error_handler_();
	if (_revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
		if (_read_handler_)
			_read_handler_(receive_time);
	if (_revents_ & EPOLLOUT)
		if (_write_handler_)
			_write_handler_();

	_handling_event_ = false;
}

void Channel::update()
{
	_in_loop_ = true;

	if (_owner_event_loop_->has_channel(this))
		_owner_event_loop_->update_channel(this);
	else
		_owner_event_loop_->add_channel(this);
}

void Channel::remove()
{
	_in_loop_ = false;
	_owner_event_loop_->remove_channel(this);
}

Channel::~Channel()
{
	assert(!_in_loop_);
	assert(!_handling_event_);
}

