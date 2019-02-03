//
// Created by kiwi on 19-1-7.
//

#ifndef KIWI_EVENT_LOOP_H
#define KIWI_EVENT_LOOP_H

#include <cassert>
#include <atomic>
#include <future>
#include <thread>
#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include "../Base/Types.h"
#include "../Base/TimerPool.h"

namespace Kiwi
{
	class Epoll;

	class Channel;

	class EventLoop
	{
	public:

		EventLoop();

		void loop();

		void stop();

		void add_channel(Channel *channel);

		void remove_channel(Channel *channel);

		void update_channel(Channel *channel);

		bool has_channel(Channel *channel);

		void run_in_loop(Type::Functor functor);

		void queue_in_loop(Type::Functor functor);

		std::future<Type::TimerID> run_after(Type::TimerHandler handler, TimeRange interval);

		void cancel_in_loop(std::future<Type::TimerID> future);

		void assert_in_event_loop_thread();

		~EventLoop();

		EventLoop(const EventLoop &) = delete;

		EventLoop &operator=(const EventLoop &) = delete;

	private:
		void wakeup();

		void handle_pending_functors();

		void wakeup_read_handler();

	private:
		static const int EPOLL_WAIT_TIME_OUT = 50;

		std::mutex _mutex_;
		std::atomic<bool> _looping_;
		std::atomic<bool> _stop_;
		std::atomic<bool> _handling_events_;
		std::atomic<bool> _handling_functors_;
		std::unique_ptr<Epoll> _epoll_ptr_;
		std::unique_ptr<TimerPool> _timer_pool_ptr_;
		std::unique_ptr<Channel> _wakeup_channel_;
		std::vector<Type::Functor> _pending_functors_;
		std::thread::id _thread_id_;
		Type::ChannelList _active_channels_;
	};
}

#endif
