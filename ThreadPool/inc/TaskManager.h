#pragma once
#include <queue>
#include <mutex>


namespace thread_pool_task
{


	class Task
	{
	public:
		Task() {};
		virtual ~Task() = 0;
		virtual void StartTask() = 0;
	};

	class Json_Task : public Task
	{
	public:
		Json_Task() {}
		virtual ~Json_Task() {}
		virtual void StartTask();
	};

	class TaskManager
	{
	public:
		TaskManager();
		~TaskManager();

		void	PushTask(Task *task);
		Task*	PopTask();
		int		GetTaskCount() const;
	private:
		std::queue<Task*>	queue_task_;
		std::mutex			mutex_task_;
	};

	class FunctionManager
	{
	public:
		FunctionManager();
		~FunctionManager();
		typedef std::function<void*> voidptr_function;
	private:
		std::queue<voidptr_function>	queue_function_;
		std::mutex						mutex_function_;
	};


}
