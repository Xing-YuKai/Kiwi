//
// Created by kiwi on 19-1-19.
//

#include "EventLoopPool.h"
#include "EventLoop.h"

using namespace Kiwi;
using namespace Kiwi::Type;

EventLoopPool::EventLoopPool(EventLoop* base_loop, size_t size = 0) :
		_base_loop_(base_loop),
		_next_(0),
		_loop_num_(size)
{
	add_loop(size);
}

EventLoop* EventLoopPool::get_loop()
{
	EventLoop* res = _base_loop_;
	if (!_loops_.empty())
	{
		res = _loops_[_next_];
		_next_ = (_next_ + 1) % _loop_num_;
	}
	return res;
}

void EventLoopPool::add_loop(size_t size)
{
	EventLoop* loop_ptr;
	bool flag = false;
	for (size_t i = 0; i < size; i++)
	{
		_threads_.emplace_back([this, &loop_ptr, &flag]
							   {
							   		EventLoop loop;
								   {
									   std::lock_guard<std::mutex> lock_guard(this->_mutex_);
									   loop_ptr = &loop;
									   flag = true;
									   this->_cv_.notify_one();
								   }
								   loop.loop();
							   });

		{
			std::unique_lock<std::mutex> unique_lock(_mutex_);
			_cv_.wait(unique_lock, [&flag] { return flag; });
			_loops_.emplace_back(loop_ptr);
			flag = false;
		}
	}
}

EventLoopPool::~EventLoopPool()
{
	for (auto ptr : _loops_)
		ptr->stop();
	for (auto &thread : _threads_)
		thread.detach();
}
