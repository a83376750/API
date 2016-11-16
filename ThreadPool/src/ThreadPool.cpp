#include "..\inc\ThreadPool.h"


namespace thread_pool
{
	ThreadPool::ThreadPool()
	{
	}


	ThreadPool::~ThreadPool()
	{
	}

	void ThreadPool::TaskPolling()
	{
		while (1)
		{
			thread_pool_task::Task *task = task_manager_.PopTask();
			if (task == nullptr)
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			else
			{
				task->StartTask();
			}
		}
	}

	int ThreadPool::GetThreadCount() const
	{
		return vec_threads_.size();
	}
}