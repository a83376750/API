#include "..\inc\TaskManager.h"
#include <iostream>

namespace thread_pool_task
{

	TaskManager::TaskManager()
	{
	}


	TaskManager::~TaskManager()
	{
	}

	void TaskManager::PushTask(Task *task)
	{
		std::lock_guard<std::mutex> lock{ mutex_task_ };
		queue_task_.emplace(task);
	}

	thread_pool_task::Task* TaskManager::PopTask()
	{
		std::lock_guard<std::mutex> lock{ mutex_task_ };
		if (queue_task_.empty())
			return nullptr;

		Task *task = queue_task_.front();
		queue_task_.pop();
		return task;
	}

	size_t TaskManager::GetTaskCount() const
	{
		return queue_task_.size();
	}

	void Json_Task::StartTask()
	{
		std::cout << "Json_Task_start!!!\n";
	}

	FunctionManager::FunctionManager()
	{
		open_flag_ = true;
	}

	FunctionManager::~FunctionManager()
	{
	}

	thread_pool_task::FunctionManager::void_function FunctionManager::PopFunction()
	{
		std::unique_lock<std::mutex> lock{ mutex_function_ };
		cv_function_.wait(
			lock, [this]()
			{
				return !queue_function_.empty() || !open_flag_;
			}
		);

		if (!open_flag_)
			return nullptr;		//这里不能使用NULL,编译时会 /*未能使函数模板“unknown-type std::invoke(_Callable &&,_Types &&...)”专用化*/
		auto fun = std::move(queue_function_.front());
		queue_function_.pop();
		return fun;
	}


	void FunctionManager::CloseManager()
	{
		open_flag_ = false;
		cv_function_.notify_all();
	}

}