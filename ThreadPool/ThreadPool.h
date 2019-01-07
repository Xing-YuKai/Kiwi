//
// Created by kiwi on 19-1-5.
//

#ifndef KIWI_THREADPOOL_H
#define KIWI_THREADPOOL_H

#include <list>
#include <thread>
#include <mutex>
#include <future>
#include <utility>
#include <memory>
#include <functional>
#include <queue>
#include "../Base/Semaphore.h"

namespace Kiwi
{
	class ThreadPool
	{
	public:
		ThreadPool(size_t size = 4);

		void increase_pool(size_t size);

		void decrease_pool(size_t size);

		template<typename F, typename... Args>
		auto commit(F &&f, Args &&... rest) -> std::future<decltype(f(rest...))>;

		~ThreadPool();

		ThreadPool &operator=(const ThreadPool &) = delete;

		ThreadPool(const ThreadPool &) = delete;

	private:
		std::list<std::thread> _pool_;
		std::queue<std::function<void()>> _task_queue_;
		std::mutex _mutex_;
		std::condition_variable _cv_;
		Semaphore _idle_thread_;
		bool _decreasing_;
		bool _stop_;
	};

	ThreadPool::ThreadPool(size_t size)
	{
		_decreasing_ = false;
		_stop_ = false;
		increase_pool(size);
	}

	void ThreadPool::increase_pool(size_t size)
	{
		for (int i = 0; i < size; i++)
		{
			_pool_.emplace_back([this]() -> void
								{
									while (true)
									{
										this->_idle_thread_.post();
										std::function<void()> task;

										{
											std::unique_lock<std::mutex> _unique_lock(this->_mutex_);
											this->_cv_.wait(_unique_lock, [this]
											{
												return this->_stop_ || this->_decreasing_ || !this->_task_queue_.empty();
											});

											if (this->_stop_ && this->_task_queue_.empty())
												return;

											if (this->_decreasing_)
											{
												for (auto itr = this->_pool_.begin(); itr != this->_pool_.end(); itr++)
												{
													if (itr->get_id() == std::this_thread::get_id())
													{
														itr->detach();
														this->_pool_.erase(itr);
														return;
													}
												}
											}

											task = std::move(this->_task_queue_.front());
											this->_task_queue_.pop();
										}
										this->_idle_thread_.wait();
										task();
									}
								});
		}
	}

	void ThreadPool::decrease_pool(size_t size)
	{
		{
			std::lock_guard<std::mutex> _lock_guard_(_mutex_);
			_decreasing_ = true;
			for (int i = 0; i < size; i++)
			{
				_cv_.notify_one();
				_idle_thread_.wait();
			}
			_decreasing_ = false;
		}
	}

	template<typename F, typename... Args>
	auto ThreadPool::commit(F &&f, Args &&... rest) -> std::future<decltype(f(rest...))>
	{
		using return_type = decltype(f(rest...));

		auto task_ptr = std::make_shared<std::packaged_task<return_type()>>(
				std::bind(std::forward<F>(f), std::forward<Args>(rest)...));

		std::future<return_type> res = task_ptr->get_future();

		{
			std::lock_guard<std::mutex> _lock_guard_(_mutex_);
			_task_queue_.emplace([task_ptr] { (*task_ptr)(); });
		}

		_cv_.notify_one();
		return res;
	}

	ThreadPool::~ThreadPool()
	{
		{
			std::lock_guard<std::mutex> _lock_guard_(_mutex_);
			_stop_ = true;
		}

		_cv_.notify_all();

		for (auto &thread : _pool_)
			thread.detach();
	}
}


#endif //KIWI_THREADPOOL_H
