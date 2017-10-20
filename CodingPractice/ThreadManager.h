#pragma once

#include "Singleton.h"
#include "ThreadPool.h"
#include "TaskQueue.h"

#include <functional>

class ThreadManager : public Singleton<ThreadManager>
{
public:
	enum Priority {
		PRIORITY_LOWEST = 0,
		PRIORITY_LOW,
		PRIORITY_NORMAL,
		PRIORITY_HIGH,
		PRIORITY_HIGHEST
	};

	ThreadManager(int, Priority _priority = PRIORITY_LOW);
	~ThreadManager();

	template <typename T>
	bool async(T &&task) {
		if (m_ThreadPool.is_this_thread_in()) {
			task();
		}
		else {
			m_TaskQueue.push_task(std::forward<T>(task));
		}
		return true;
	}

private:

	void run();

private:
	int m_threadNum;
	ThreadPool m_ThreadPool;
	TaskQueue m_TaskQueue;
};

ThreadManager::ThreadManager(int a_num, Priority _priority /*= PRIORITY_LOW*/)
	:m_threadNum(a_num)
{
	for (int i = 0; i < m_threadNum; ++i)
	{
		m_ThreadPool.create_thread(bind(&ThreadManager::run, this));
	}
}

void ThreadManager::run()
{
	function<void(void)> task;
	while (1)
	{
		if (m_TaskQueue.get_task(task))
		{
			try {
				task();	//#Allen could add timer here
			}
			catch (std::exception &ex) {
				printf("Exception @thread %i,exit \n", this_thread::get_id());
				break;
			}
			task = NULL;
		}
	}
}
