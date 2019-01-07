//
// Created by kiwi on 19-1-7.
//

#ifndef KIWI_EVENT_LOOP_H
#define KIWI_EVENT_LOOP_H

#include <atomic>
#include <thread>
#include <iostream>

namespace Kiwi
{
	class EventLoop
	{
	public:
		EventLoop();

		void loop();

		void quit();

		void assert_in_event_loop_thread();

		~EventLoop();

		EventLoop(const EventLoop &) = delete;

		EventLoop &operator=(const EventLoop &) = delete;

	private:
		std::atomic<bool> _looping_;
		std::thread::id _thread_id_;

	};
}

#endif
