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
#include "../Base/Types.h"

namespace Kiwi
{
	class Epoll
	{
	public:

		explicit Epoll(EventLoop* event_loop);

		TimeRange poll(Type::ChannelList &active_channels, int time_out_ms);

		void add_channel(Channel *channel);

		void remove_channel(Channel *channel);

		void update_channel(Channel *channel);

		bool has_channel(Channel *channel);


		~Epoll();

		Epoll(const Epoll &) = delete;

		Epoll &operator=(const Epoll &) = delete;

	private:

		void epoll_add(Channel *channel);

		void epoll_del(Channel *channel);

		void epoll_mod(Channel *channel);

	private:
		static const int INIT_EVENT_LIST_SIZE = 16;
		Type::ChannelMap _channels_;
		Type::EventList _event_list_;
		EventLoop* _owner_event_loop_;
		int _epoll_fd_;
	};
}

#endif //KIWI_EPOLL_H
