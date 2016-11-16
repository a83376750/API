#pragma once
#include <vector>
#include <thread>
#include "TaskManager.h"

namespace thread_pool
{
	class ThreadPool
	{
	public:
		ThreadPool();
		~ThreadPool();

		void	TaskPolling();
		int		GetThreadCount() const;
	private:

		thread_pool_task::TaskManager	task_manager_;
		std::vector<std::thread>		vec_threads_;

	};

}