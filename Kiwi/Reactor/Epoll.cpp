//
// Created by kiwi on 19-1-7.
//

#include "Epoll.h"

using namespace Kiwi;
using namespace Kiwi::Type;

Epoll::Epoll(EventLoop* event_loop) :
		_epoll_fd_(epoll_create(INIT_EVENT_LIST_SIZE)),
		_owner_event_loop_(event_loop),
		_event_list_(INIT_EVENT_LIST_SIZE) {}

TimeRange Epoll::poll(Type::ChannelList &active_channels, int time_out_ms)
{
	flag:
	int event_count = epoll_wait(_epoll_fd_, _event_list_.begin().base(), static_cast<int>(_event_list_.size()),
								 time_out_ms);
	TimeRange time = TimeRange::now();
	if (event_count < 0)
	{
		switch (errno)
		{
			case EINTR:
				goto flag;
			default:
				std::cerr << "Epoll poll error : " << errno << " " << strerror(errno) << std::endl;
				std::terminate();
		}
	} else
	{
		for (int i = 0; i < event_count; i++)
		{
			Channel *channel = reinterpret_cast<Channel *>(_event_list_[i].data.ptr);
			channel->set_revents(_event_list_[i].events);
			active_channels.emplace_back(channel);
		}
	}
	return time;
}

void Epoll::add_channel(Channel *channel)
{
	int fd = channel->get_fd();
	assert(_channels_.find(fd) == _channels_.end());
	_channels_.emplace(fd, channel);
	epoll_add(channel);
}

void Epoll::remove_channel(Channel *channel)
{
	int fd = channel->get_fd();
	assert(_channels_.find(fd) != _channels_.end());
	_channels_.erase(fd);
	epoll_del(channel);
}

void Epoll::update_channel(Channel *channel)
{
	int fd = channel->get_fd();
	assert(_channels_.find(fd) != _channels_.end());
	epoll_mod(channel);
}

bool Epoll::has_channel(Channel *channel)
{
	int fd = channel->get_fd();
	return _channels_.find(fd) != _channels_.end();
}

Epoll::~Epoll()
{
	close(_epoll_fd_);
}

void Epoll::epoll_add(Channel *channel)
{
	int fd = channel->get_fd();
	struct epoll_event event{};
	event.data.ptr = channel;
	event.events = channel->get_events();
	int errno_backup = errno;
	int retval = epoll_ctl(_epoll_fd_, EPOLL_CTL_ADD, fd, &event);
	if (retval < 0)
	{
		switch (errno)
		{
			case EEXIST:
				errno = errno_backup;
				return;
			default:
				std::cerr << "Epoll epoll_add error : " << errno << " " << strerror(errno) << std::endl;
				std::terminate();
		}
	}
}

void Epoll::epoll_del(Channel *channel)
{
	int fd = channel->get_fd();
	struct epoll_event event{};
	event.data.ptr = channel;
	event.events = channel->get_events();
	int retval = epoll_ctl(_epoll_fd_, EPOLL_CTL_DEL, fd, &event);
	if (retval < 0)
	{
		std::cerr << "Epoll epoll_del error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}

void Epoll::epoll_mod(Channel *channel)
{
	int fd = channel->get_fd();
	struct epoll_event event{};
	event.data.ptr = channel;
	event.events = channel->get_events();
	int retval = epoll_ctl(_epoll_fd_, EPOLL_CTL_MOD, fd, &event);
	if (retval < 0)
	{
		std::cerr << "Epoll epoll_mod error : " << errno << " " << strerror(errno) << std::endl;
		std::terminate();
	}
}