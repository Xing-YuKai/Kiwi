//
// Created by kiwi on 19-1-22.
//

#ifndef KIWI_TIMERPOOL_H
#define KIWI_TIMERPOOL_H

#include <functional>
#include <vector>
#include "TimerNode.h"

namespace Kiwi
{
	class TimerPool
	{
	public:
		using TimerHandler = std::function<void()>;
		using TimerList = std::vector<TimerNode *>;
	public:
		TimerPool();

		start_timer(const TimerHandler &handler, TimerPool);

		stop_timer();

		~TimerPool();

		TimerPool(const TimerPool &) = delete;

		TimerPool &operator=(const TimerPool &) = delete;

	private:
		static const int TV_BITS = 8;
		static const int TV_SIZE = 1 << TV_BITS;
		static const int TV_MASK = TV_SIZE - 1;
		static const int TV_NUM = 4;

	private:
		TimerList _buckets_[TV_NUM][TV_SIZE];
	};
}

#endif //KIWI_TIMERPOOL_H
