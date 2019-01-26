//
// Created by kiwi on 19-1-22.
//

#include "TimerPool.h"

void Kiwi::TimerPool::tick()
{
	int index = _jiffy_ & TV_MASK;
	for (int i = 1; i <= 3; i++)
	{
		if (index == 0)
		{
			index = (_jiffy_ >> (TV_BITS * i)) & TV_MASK;
			cascade(1,index);
		}
	}
	execute();
	_jiffy_++;
}

void Kiwi::TimerPool::execute()
{
	int index = _jiffy_ & TV_MASK;
	TimerList expired_timer;
	_buckets_[0][index].swap(expired_timer);
	for (auto node_ptr:expired_timer)
	{
		if (!node_ptr->_stopped_ && node_ptr->_handler_)
			node_ptr->_handler_();
		_timer_node_ref_.erase(node_ptr->_id_);
	}
}

void Kiwi::TimerPool::cascade(const int &tv_num, const int &tv_index)
{
	TimerList list;
	_buckets_[tv_num][tv_index].swap(list);

	for (auto node_ptr:list)
		add_timer_node(node_ptr);
}

void Kiwi::TimerPool::add_timer_node(TimerNodePtr node_ptr)
{
	uint64_t expire = node_ptr->_expire_time_;
	uint64_t interval = node_ptr->_expire_time_ - _jiffy_;
	TimerList *list_ptr = nullptr;
	if (interval < (1 << TV_BITS))
	{
		int index = expire & (TV_MASK);
		list_ptr = &_buckets_[0][index];
	} else if (interval < (1 << TV_BITS * 2))
	{
		int index = (expire >> TV_BITS) & (TV_MASK);
		list_ptr = &_buckets_[1][index];
	} else if (interval < (1 << TV_BITS * 3))
	{
		int index = (expire >> TV_BITS * 2) & (TV_MASK);
		list_ptr = &_buckets_[2][index];
	} else if (interval < (1 << TV_BITS * 4))
	{
		int index = (expire >> TV_BITS * 3) & (TV_MASK);
		list_ptr = &_buckets_[3][index];
	}
	list_ptr->emplace_back(node_ptr);
}

Kiwi::TimerID Kiwi::TimerPool::start_timer(const Kiwi::TimeRange &interval, const Kiwi::TimerHandler &handler)
{
	uint64_t time_units = interval.cast_to_10_milliseconds();
	if (UINT64_MAX - _jiffy_ < time_units)
	{
		std::cerr << "TimerPool start_timer error : " << "The interval is too long for this TimerPool" << std::endl
				  << "Current jiffy of this TimerPool is : " << _jiffy_ << " * 10ms" << std::endl
				  << "The interval is : " << time_units << " * 10ms" << std::endl;
		std::terminate();
	}

	TimerNodePtr node_ptr = std::make_shared();
	node_ptr->_id_ = ++_id_counter_;
	node_ptr->_handler_ = handler;
	node_ptr->_expire_time_ = time_units + _jiffy_;
	add_timer_node(node_ptr);
	_timer_node_ref_[node_ptr->_id_] = node_ptr;
	return node_ptr->_id_;
}

void Kiwi::TimerPool::stop_timer(const Kiwi::TimerID &timer_id)
{
	TimerNodePtr node_ptr = _timer_node_ref_[timer_id];
	node_ptr->_stopped_ = true;
}

Kiwi::TimerPool::TimerPool()
{
	_timer_node_ref_.rehash(128);
	_pool_time_ = TimeRange::now().cast_to_10_milliseconds();
}
