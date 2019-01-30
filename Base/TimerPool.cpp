//
// Created by kiwi on 19-1-22.
//

#include "TimerPool.h"

using namespace Kiwi;
using namespace Kiwi::Type;

TimerPool::TimerPool() :
		_id_counter_(0),
		_jiffy_(0),
		_pool_time_(TimeRange::now().cast_to_10_milliseconds())
{
	_timers_.rehash(128);
}

TimerID TimerPool::start_timer(const TimeRange &interval, const TimerHandler &handler)
{
	uint64_t time_units = interval.cast_to_10_milliseconds();
	if (UINT64_MAX - _jiffy_ < time_units)
	{
		std::cerr << "TimerPool start_timer error : " << "The interval is too long for this TimerPool" << std::endl
				  << "Current jiffy of this TimerPool is : " << _jiffy_ << " * 10ms" << std::endl
				  << "The interval is : " << time_units << " * 10ms" << std::endl;
		std::terminate();
	}

	TimerNodePtr node_ptr = std::make_shared<TimerNode>();
	node_ptr->_id_ = ++_id_counter_;
	node_ptr->_handler_ = handler;
	node_ptr->_expire_time_ = time_units + _jiffy_;
	add_timer_node(node_ptr);
	_timers_.emplace(node_ptr->_id_, node_ptr);
	return node_ptr->_id_;
}

void TimerPool::stop_timer(const TimerID &timer_id)
{
	TimerNodePtr node_ptr = _timers_[timer_id];
	node_ptr->_stopped_ = true;
}

void TimerPool::update()
{
	uint64_t current = TimeRange::now().cast_to_10_milliseconds();
	uint64_t ticks = current - _pool_time_;
	_pool_time_ = current;
	for (uint64_t i = 1; i <= ticks; i++)
		tick();
}

void TimerPool::tick()
{
	size_t index = _jiffy_ & TV_MASK;
	for (size_t i = 1; i <= 7; i++)
	{
		if (index == 0)
		{
			index = (_jiffy_ >> (TV_BITS * i)) & TV_MASK;
			cascade(i, index);
		}
	}
	execute();
	_jiffy_++;
}

void TimerPool::execute()
{
	size_t index = _jiffy_ & TV_MASK;
	TimerList expired_timer;
	_buckets_[0][index].swap(expired_timer);
	for (const auto &node_ptr:expired_timer)
	{
		if (!node_ptr->_stopped_ && node_ptr->_handler_)
			node_ptr->_handler_();
		_timers_.erase(node_ptr->_id_);
	}
}

void TimerPool::cascade(const size_t &tv_num, const size_t &tv_index)
{
	TimerList list;
	_buckets_[tv_num][tv_index].swap(list);

	for (const auto &node_ptr:list)
		add_timer_node(node_ptr);
}

void TimerPool::add_timer_node(const TimerNodePtr &node_ptr)
{
	uint64_t expire = node_ptr->_expire_time_;
	uint64_t interval = node_ptr->_expire_time_ - _jiffy_;
	if (interval < (1ULL << TV_BITS))
	{
		size_t index = expire & (TV_MASK);
		_buckets_[0][index].emplace_back(node_ptr);
	} else if (interval < (1ULL << TV_BITS * 2))
	{
		size_t index = (expire >> TV_BITS) & (TV_MASK);
		_buckets_[1][index].emplace_back(node_ptr);
	} else if (interval < (1ULL << TV_BITS * 3))
	{
		size_t index = (expire >> TV_BITS * 2) & (TV_MASK);
		_buckets_[2][index].emplace_back(node_ptr);
	} else if (interval < (1ULL << TV_BITS * 4))
	{
		size_t index = (expire >> TV_BITS * 3) & (TV_MASK);
		_buckets_[3][index].emplace_back(node_ptr);
	} else if (interval < (1ULL << TV_BITS * 5))
	{
		size_t index = (expire >> TV_BITS * 4) & (TV_MASK);
		_buckets_[4][index].emplace_back(node_ptr);
	} else if (interval < (1ULL << TV_BITS * 6))
	{
		size_t index = (expire >> TV_BITS * 5) & (TV_MASK);
		_buckets_[5][index].emplace_back(node_ptr);
	} else if (interval < (1ULL << TV_BITS * 7))
	{
		size_t index = (expire >> TV_BITS * 6) & (TV_MASK);
		_buckets_[6][index].emplace_back(node_ptr);
	} else if (interval < UINT64_MAX)
	{
		size_t index = (expire >> TV_BITS * 7) & (TV_MASK);
		_buckets_[7][index].emplace_back(node_ptr);
	}
}