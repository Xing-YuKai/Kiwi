//
// Created by kiwi on 19-1-7.
//

#include "Epoll.h"

Kiwi::Epoll::Epoll(Kiwi::EventLoop *event_loop) : _epoll_fd_(epoll_create(16)), _owner_event_loop_(event_loop),
{

}

void Kiwi::Epoll::poll(Kiwi::Epoll::ChannelList &active_channel)
{

}

void Kiwi::Epoll::epoll_add(Kiwi::Channel channel)
{
	int fd = channel.get_fd();
	struct epoll_event event{};
	event.data.fd = fd;
	event.events = channel.get_events();
	int retval = epoll_ctl(_epoll_fd_, EPOLL_CTL_ADD, fd, &event);
	if (retval < 0)
	{
		switch (errno)
		{
			case EEXIST:
				return;
			default:
				std::cerr << "Epoll epoll_add error : " << errno << " " << strerror(errno) << std::endl;
				std::terminate();
		}
	}
}

void Kiwi::Epoll::epoll_del(Kiwi::Channel channel)
{
	int fd = channel.get_fd();
	struct epoll_event event{};
	event.data.fd = fd;
	event.events = channel.get_events();
	int retval = epoll_ctl(_epoll_fd_, EPOLL_CTL_MOD, fd, &event);
	if (retval < 0)
	{
		std::cerr << "Epoll epoll_mod error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();

	}
}

void Kiwi::Epoll::epoll_mod(Kiwi::Channel channel)
{
	int fd = channel.get_fd();
	struct epoll_event event{};
	event.data.fd = fd;
	event.events = channel.get_events();
	int retval = epoll_ctl(_epoll_fd_, EPOLL_CTL_MOD, fd, &event);
	if (retval < 0)
	{
		std::cerr << "Epoll epoll_mod error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();

	}
}

