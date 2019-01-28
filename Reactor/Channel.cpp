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
		_handling_event_(false),
		_in_loop_(false){}


void Channel::handle_event()
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


Channel::~Channel()
{

}

