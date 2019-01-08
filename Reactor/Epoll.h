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
		using EventList = std::vector<struct epoll_event>;
	public:
		explicit Epoll(EventLoop *event_loop);

		void poll(ChannelList &active_channels);

		void epoll_add(const Channel& channel);
		void epoll_del(const Channel& channel);
		void epoll_mod(const Channel& channel);

		~Epoll();

		Epoll(const Epoll &) = delete;

		Epoll &operator=(const Epoll &) = delete;

	private:
		static const int INIT_EVENT_LIST_SIZE = 16;
		void update();
		EventList _event_list_;
		EventLoop *_owner_event_loop_;
		int _epoll_fd_;
	};
}

#endif //KIWI_EPOLL_H
