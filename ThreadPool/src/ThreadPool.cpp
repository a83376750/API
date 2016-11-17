#include "..\inc\ThreadPool.h"


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

	}

	void ThreadPool::StartThreadPool()
	{
		for (int i = 0; i < max_thread_count_; ++i)
			vec_threads_.emplace_back(&thread_pool::ThreadPool::TaskPolling, this);
	}

	void ThreadPool::TaskPolling()
	{
		while (true)
		{
			auto fun = function_manager_.PopFunction();
			fun();
		}
	}

	size_t ThreadPool::GetThreadCount() const
	{
		return vec_threads_.size();
	}


}
