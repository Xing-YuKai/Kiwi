//
// Created by kiwi on 19-1-22.
//

#ifndef KIWI_TIMERPOOL_H
#define KIWI_TIMERPOOL_H

#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include "TimerNode.h"
#include "TimeRange.h"

namespace Kiwi
{
	class TimerPool
	{
	public:
		TimerPool();

		Type::TimerID start_timer(const TimeRange &interval, const Type::TimerHandler &handler);

		void stop_timer(const Type::TimerID &timer_id);

		void update();

		~TimerPool() = default;

		TimerPool(const TimerPool &) = delete;

		TimerPool &operator=(const TimerPool &) = delete;

	private:
		void tick();

		void execute();

		void cascade(const size_t &tv_num, const size_t &tv_index);

		void add_timer_node(const Type::TimerNodePtr &node_ptr);

	private:
		static const size_t TV_BITS = 8;
		static const size_t TV_SIZE = 1ULL << TV_BITS;
		static const size_t TV_MASK = TV_SIZE - 1;
		static const size_t TV_MAX_NUM = 8;
	private:
		uint64_t _pool_time_;
		uint64_t _jiffy_;
		Type::TimerList _buckets_[TV_MAX_NUM][TV_SIZE];
		std::unordered_map<Type::TimerID, Type::TimerNodePtr> _timers_;
		uint32_t _id_counter_;
	};
}

#endif //KIWI_TIMERPOOL_H
