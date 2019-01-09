//
// Created by kiwi on 19-1-7.
//

#include "Channel.h"

Kiwi::Channel::Channel(Kiwi::EventLoop *loop, int fd) :
		_owner_event_loop_(loop),
		_fd_(fd),
		_events_(0),
		_revents_(0),
		_handling_event_(false),
		_in_loop_(false),{}


void Kiwi::Channel::handle_event()
{
	if (_revents_ & EPOLLERR)
		if (_error_handler_)
			_error_handler_();
	if (_revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
		if (_read_handler_)
			_read_handler_();
	if (_revents_ & EPOLLOUT)
		if (_write_handler_)
			_write_handler_();
}


Kiwi::Channel::~Channel()
{

}

void Kiwi::Channel::update()
{
	_owner_event_loop_->update_channel(*this);
}

