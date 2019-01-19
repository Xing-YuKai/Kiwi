//
// Created by kiwi on 19-1-19.
//

#include "EventLoopPool.h"

Kiwi::EventLoopPool::EventLoopPool(Kiwi::EventLoop *base_loop, size_t size = 0) :
		_base_loop_(base_loop),
		_next_(0),
		_loop_num_(size)
{
	add_loop(size);
}

Kiwi::EventLoop *Kiwi::EventLoopPool::get_loop()
{
	EventLoop *res = _base_loop_;
	if (!_loops_.empty())
	{
		res = _loops_[_next_];
		_next_ = (_next_ + 1) % _loop_num_;
	}
	return res;
}

void Kiwi::EventLoopPool::add_loop(size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		_threads_.emplace_back([] { EventLoop loop; })
	}
}
