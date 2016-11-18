#pragma once
#include <queue>
#include <mutex>
#include <future>
#include <atomic>

namespace thread_pool_task
{

	//不使用
	class Task
	{
	public:
		Task() {};
		virtual ~Task() = 0;
		virtual void StartTask() = 0;
	};

	//不使用
	class Json_Task : public Task
	{
	public:
		Json_Task() {}
		virtual ~Json_Task() {}
		virtual void StartTask();
	};

	//不使用
	class TaskManager
	{
	public:
		TaskManager();
		~TaskManager();

		void	PushTask(Task *task);
		Task*	PopTask();
		size_t		GetTaskCount() const;
	private:
		std::queue<Task*>	queue_task_;
		std::mutex			mutex_task_;
	};

	class FunctionManager
	{
	public:
		FunctionManager();
		~FunctionManager();
		typedef std::function<void()> void_function;

		template<class F, class... Args>
		auto			PushFunction(F&& f, Args&&... args) ->std::future<decltype(f(args...))>
		{
			using ResType = decltype(f(args...));
			auto task = std::make_shared<std::packaged_task<ResType()>>(
				std::bind(std::forward<F>(f), std::forward<Args>(args)...));

			std::lock_guard<std::mutex> lock{ mutex_function_ };
			queue_function_.emplace(
				[task]() 
				{
					(*task)();
				}
			);
			cv_function_.notify_all();

			std::future<ResType> future = task->get_future();
			return future;
		};
		void_function	PopFunction();
		void			CloseManager();
	private:
		std::atomic<bool>				open_flag_;
		std::condition_variable			cv_function_;
		std::queue<void_function>		queue_function_;
		std::mutex						mutex_function_;
	};


}