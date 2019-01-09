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

		void set_read_handler(const EventHandler &handler) { _read_handler_ = handler; }

		void set_write_handler(const EventHandler &handler) { _write_handler_ = handler; }

		void set_error_handler(const EventHandler &handler) { _error_handler_ = handler; }

		void enable_reading() {_events_|=READ_EVENT;update();}

		void disable_reading() {_events_&=~READ_EVENT;update();}

		void enable_writing() {_events_|=WRITE_EVENT;update();}

		void disable_writing() {_events_&=~WRITE_EVENT;update();}

		void disable_all() {_events_=NONE_EVENT;update();}

		bool is_reading() const {return _events_&READ_EVENT;}

		bool is_writing() const {return _events_&WRITE_EVENT;}

		bool is_none_event() const {return _events_==NONE_EVENT;}

		void handle_event();

		void set_events(uint32_t events) { _events_ = events; }

		void set_revents(uint32_t revents) { _revents_ = revents; }

		uint32_t get_events() const { return _events_; }

		int get_fd() const { return _fd_; }

		EventLoop *get_loop() const { return _owner_event_loop_; }

		~Channel();

		Channel(const Channel &) = delete;

		Channel &operator=(const Channel &) = delete;

	private:
		void update();

		EventLoop *_owner_event_loop_;
		const int _fd_;

		bool _in_loop_;
		bool _handling_event_;

		static const int NONE_EVENT = 0;
		static const int READ_EVENT = EPOLLIN | EPOLLPRI | EPOLLRDHUP;
		static const int WRITE_EVENT = EPOLLOUT;

		uint32_t _events_;
		uint32_t _revents_;

		EventHandler _read_handler_;
		EventHandler _write_handler_;
		EventHandler _error_handler_;
	};
}

#endif //KIWI_CHANNEL_H
