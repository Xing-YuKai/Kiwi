//
// Created by kiwi on 19-1-7.
//

#ifndef KIWI_CHANNEL_H
#define KIWI_CHANNEL_H

#include <functional>
#include <sys/epoll.h>
#include "EventLoop.h"

namespace Kiwi
{
	class Channel
	{
		using EventHandler = std::function<void()>;
	public:
		Channel(EventLoop *loop, int fd);

		void set_read_handler(const EventHandler &handler);

		void set_write_handler(const EventHandler &handler);

		void set_error_handler(const EventHandler &handler);

		void handle_event();

		void set_events(uint32_t events);

		void set_revents(uint32_t revents);

		uint32_t get_events() const;

		int get_fd() const;

		EventLoop *get_loop() const;

		~Channel();

		Channel(const Channel &) = delete;

		Channel &operator=(const Channel &) = delete;

	private:
		EventLoop *_owner_event_loop_;
		const int _fd_;

		uint32_t _events_;
		uint32_t _revents_;

		EventHandler _read_handler_;
		EventHandler _write_handler_;
		EventHandler _error_handler_;
	};
}

#endif //KIWI_CHANNEL_H
