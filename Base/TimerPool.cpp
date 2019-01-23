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

}
