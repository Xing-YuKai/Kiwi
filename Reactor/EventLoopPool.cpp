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
		EventLoop *loop_ptr;
		_threads_.emplace_back([this, &loop_ptr]
							   {
								   EventLoop loop;
								   {
									   std::unique_lock<std::mutex> unique_lock(this->_mutex_);
									   loop_ptr = &loop;
									   _cv_.notify_one();
								   }
							   });
		{
			std::unique_lock<std::mutex> unique_lock(_mutex_);
			_cv_.wait(unique_lock);
			_loops_.emplace_back(loop_ptr);
		}
	}
}
