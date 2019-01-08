//
// Created by kiwi on 19-1-7.
//

#ifndef KIWI_EPOLL_H
#define KIWI_EPOLL_H

#include <sys/epoll.h>
#include <cerrno>
#include <cstring>
#include <vector>
#include <memory>
#include "EventLoop.h"
#include "Channel.h"

namespace Kiwi
{
	class Epoll
	{
		using ChannelList = std::vector<std::shared_ptr<Channel>>;
	public:
		Epoll(EventLoop *event_loop);

		void poll(ChannelList &active_channel);

		void epoll_add(Channel channel);
		void epoll_del(Channel channel);
		void epoll_mod(Channel channel);

		~Epoll();

		Epoll(const Epoll &) = delete;

		Epoll &operator=(const Epoll &) = delete;

	private:
		static const int;
		EventLoop *_owner_event_loop_;
		int _epoll_fd_;
	};
}

#endif //KIWI_EPOLL_H
