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

	int TaskManager::GetTaskCount() const
	{
		return queue_task_.size();
	}

	void Json_Task::StartTask()
	{
		std::cout << "Json_Task_start!!!\n";
	}

	FunctionManager::FunctionManager()
	{

	}

	FunctionManager::~FunctionManager()
	{

	}

}