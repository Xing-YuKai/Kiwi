//
// Created by kiwi on 19-1-7.
//

#include "Channel.h"

Kiwi::Channel::Channel(Kiwi::EventLoop *loop, int fd) :
		_owner_event_loop_(loop),
		_fd_(fd),
		_events_(0),
		_revents_(0) {}

void Kiwi::Channel::set_read_handler(const Kiwi::Channel::EventHandler &handler)
{
	_read_handler_ = handler;
}

void Kiwi::Channel::set_write_handler(const Kiwi::Channel::EventHandler &handler)
{
	_write_handler_ = handler;
}

void Kiwi::Channel::set_error_handler(const Kiwi::Channel::EventHandler &handler)
{
	_error_handler_ = handler
	''
}

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

void Kiwi::Channel::set_events(uint32_t events)
{
	_events_ = events;
}

void Kiwi::Channel::set_revents(uint32_t revents)
{
	_revents_ = revents;
}

uint32_t Kiwi::Channel::get_events() const
{
	return _events_;
}

int Kiwi::Channel::get_fd() const
{
	return _fd_;
}

Kiwi::EventLoop *Kiwi::Channel::get_loop() const
{
	return _owner_event_loop_;
}

Kiwi::Channel::~Channel()
{

}

