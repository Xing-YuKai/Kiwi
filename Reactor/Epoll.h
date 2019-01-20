//
// Created by kiwi on 19-1-7.
//

#ifndef KIWI_EPOLL_H
#define KIWI_EPOLL_H

#include <sys/epoll.h>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <memory>
#include <map>
#include "EventLoop.h"
#include "Channel.h"

namespace Kiwi
{
	class Epoll
	{
		using ChannelList = std::vector<Channel *>;
		using ChannelMap = std::map<int, Channel *>;
		using EventList = std::vector<struct epoll_event>;
	public:
		explicit Epoll(EventLoop *event_loop);

		void poll(ChannelList &active_channels);

		void add_channel(Channel *channel);

		void remove_channel(Channel *channel);

		void update_channel(Channel *channel);

		~Epoll();

		Epoll(const Epoll &) = delete;

		Epoll &operator=(const Epoll &) = delete;

	private:
		void epoll_add(Channel *channel);

		void epoll_del(Channel *channel);

		void epoll_mod(Channel *channel);

	private:
		static const int INIT_EVENT_LIST_SIZE = 16;
		ChannelMap _channels_;
		EventList _event_list_;
		EventLoop *_owner_event_loop_;
		int _epoll_fd_;
	};
}

#endif //KIWI_EPOLL_H
