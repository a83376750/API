#include "..\inc\ThreadPool.h"
#include <iostream>

namespace thread_pool
{
	ThreadPool::ThreadPool()
	{
		max_thread_count_ = 4;
		StartThreadPool();
	}


	ThreadPool::ThreadPool(size_t max_thread_count)
	{
		max_thread_count_ = max_thread_count;
		StartThreadPool();
	}

	ThreadPool::~ThreadPool()
	{
		CloseThreadPool();
	}

	void ThreadPool::StartThreadPool()
	{
		if (vec_threads_.empty())
		{
			open_flag_ = true;
			for (int i = 0; i < max_thread_count_; ++i)
				vec_threads_.emplace_back(&thread_pool::ThreadPool::TaskPolling, this);
		}
		else
		{
			CloseThreadPool();
			StartThreadPool();
		}
	}

	void ThreadPool::CloseThreadPool()
	{
		open_flag_ = false;
		function_manager_.CloseManager();
		for (auto& thread : vec_threads_)
		{
			thread.join();
		}
		vec_threads_.clear();
	}

	void ThreadPool::TaskPolling()
	{
		while (open_flag_)
		{
			auto fun = function_manager_.PopFunction();
			if (fun)
				fun();
		}
		
		std::cout << "跳出循环 线程:" << std::this_thread::get_id() << std::endl;
	}

	size_t ThreadPool::GetThreadCount() const
	{
		return vec_threads_.size();
	}


}
