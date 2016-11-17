#include "..\inc\ThreadPool.h"


namespace thread_pool
{
	ThreadPool::ThreadPool()
	{
	}


	ThreadPool::~ThreadPool()
	{
	}

	void ThreadPool::StartThreadPool()
	{
		for (int i = 0; i < MAX_THREAD_COUNT; ++i)
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

	void ThreadPool::PushTask()
	{
		function_manager_.PushFunction(fprint);
	}

}


void fprint()
{
	printf("hello threadID:%d\n", std::this_thread::get_id());
}
