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
		ThreadPool(size_t max_thread_count);
		~ThreadPool();
		void	StartThreadPool();
		void	TaskPolling();
		size_t	GetThreadCount() const;

		template<class F, class... Args>
		void	PushTask(F&& f, Args&&... args)
		{
			function_manager_.PushFunction(f, args...);
		}
	private:

		thread_pool_task::FunctionManager	function_manager_;
		std::vector<std::thread>			vec_threads_;
		size_t								max_thread_count_;
	};

}

void fprint();