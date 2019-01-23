//
// Created by kiwi on 19-1-22.
//

#include "TimerPool.h"

void Kiwi::TimerPool::tick()
{
	int index = _jiffy_ & TV_MASK;

}

void Kiwi::TimerPool::execute()
{
	int index = _jiffy_ & TV_MASK;
	TimerList expired_timer;
	_buckets_[0][index].swap(expired_timer);
	for (auto node_ptr:expired_timer)
	{
		if (!node_ptr->_stoped_ && node_ptr->_handler_)
			node_ptr->_handler_();
		_timer_node_ref_.erase(node_ptr->_id_);
		delete (node_ptr);
		node_ptr = nullptr;
	}
}

void Kiwi::TimerPool::cascade(const int &tv_num, const int &tv_index)
{

}

void Kiwi::TimerPool::add_timer_node(Kiwi::TimerNode *node_ptr)
{
	uint32_t expire = node_ptr->_expire_time_
}

Kiwi::TimerID Kiwi::TimerPool::start_timer(const Kiwi::TimeRange &time, const Kiwi::TimerHandler &handler)
{
	uint32_t time_units = time.cast_to_10_milliseconds();
	if (UINT32_MAX - _jiffy_ < time_units)
	{
		//std::cerr << "TimeRange cast_to_milliseconds error : " << "Overflow" << std::endl;
		std::terminate();
	}

	TimerNode *node_ptr = new TimerNode;
	node_ptr->_id_ = ++_id_counter_;
	node_ptr->_handler_ = handler;
	node_ptr->_expire_time_ = time_units + _jiffy_;
	add_timer_node(node_ptr);
	_timer_node_ref_[node_ptr->_id_] = node_ptr;
	return node_ptr->_id_;
}
