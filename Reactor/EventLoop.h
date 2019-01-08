//
// Created by kiwi on 19-1-7.
//

#ifndef KIWI_EVENT_LOOP_H
#define KIWI_EVENT_LOOP_H

#include <atomic>
#include <thread>
#include <iostream>
#include <vector>
#include <memory>
#include "Channel.h"
#include "Epoll.h"
namespace Kiwi
{
	class EventLoop
	{
		using ChannelList = std::vector<std::shared_ptr<Channel>>;
	public:
		EventLoop();

		void loop();

		void stop();

		void assert_in_event_loop_thread();

		~EventLoop();

		EventLoop(const EventLoop &) = delete;

		EventLoop &operator=(const EventLoop &) = delete;

	private:
		std::atomic<bool> _looping_;
		std::atomic<bool> _stop_;
		std::unique_ptr<Epoll>  _epoll_ptr_;
		std::thread::id _thread_id_;
		ChannelList _active_channels_;
	};
}

#endif
