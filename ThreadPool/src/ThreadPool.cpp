#include "..\inc\ThreadPool.h"


namespace thread_pool
{
	ThreadPool::ThreadPool()
	{
		max_thread_count_ = 10;
	}


	ThreadPool::ThreadPool(size_t max_thread_count)
	{
		max_thread_count_ = max_thread_count;
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
			//function_manager_.PushFunction(fprint);
			//thread_pool_task::Task *task = function_manager_.PopTask();
			//if (task == nullptr)
			//{
			//	std::this_thread::sleep_for(std::chrono::seconds(1));
			//}
			//else
			//{
			//	task->StartTask();
			//}
	}

	size_t ThreadPool::GetThreadCount() const
	{
		return vec_threads_.size();
	}


}


void fprint()
{
	printf("hello threadID:%d\n", std::this_thread::get_id());
}
