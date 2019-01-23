//
// Created by kiwi on 19-1-22.
//

#ifndef KIWI_TIMERPOOL_H
#define KIWI_TIMERPOOL_H

#include <functional>
#include <unordered_map>
#include <vector>
#include "TimerNode.h"
#include "TimeRange.h"

namespace Kiwi
{
	class TimerPool
	{
	public:
		using TimerList = std::vector<TimerNode *>;
	public:
		TimerPool();

		TimerID start_timer(const TimeRange &time, const TimerHandler &handler);

		bool stop_timer(const TimerID &timer_id);

		~TimerPool();

		TimerPool(const TimerPool &) = delete;

		TimerPool &operator=(const TimerPool &) = delete;

	private:
		void tick();

		void execute();

		void cascade(const int &tv_num, const int &tv_index);

		void add_timer_node(TimerNode *node_ptr);

	private:
		static const int TV_BITS = 8;
		static const int TV_SIZE = 1 << TV_BITS;
		static const int TV_MASK = TV_SIZE - 1;
		static const int TV_MAX_NUM = 4;
	private:
		int64_t _pool_time_;
		int64_t _jiffy_;
		TimerList _buckets_[TV_MAX_NUM][TV_SIZE];
		std::unordered_map<TimerID, TimerNode *> _timer_node_ref_;
	};
}

#endif //KIWI_TIMERPOOL_H
