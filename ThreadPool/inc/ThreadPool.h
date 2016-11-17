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
		void	StartThreadPool();
		void	TaskPolling();
		size_t	GetThreadCount() const;
		void	PushTask();
	private:

		//thread_pool_task::TaskManager	task_manager_;
		thread_pool_task::FunctionManager	function_manager_;
		std::vector<std::thread>			vec_threads_;
		const size_t						MAX_THREAD_COUNT = 10;
	};

}

void fprint();