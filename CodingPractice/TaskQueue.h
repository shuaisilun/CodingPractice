#pragma once

#include <deque>
#include <atomic>
#include <mutex>
#include <functional>

#include "semaphore.h"

class TaskQueue
{
public:
	TaskQueue() {}

	template <typename T>
	void push_task(T &&a_taskFunc)
	{
		{
			lock_guard<mutex> lock(m_mutex);
			m_TaskQueue.emplace_back(std::forward<T>(a_taskFunc));
		}
		sem.post();
	}

	bool get_task(function<void(void)> &o_task)
	{
		sem.wait();
		lock_guard<mutex> lock(m_mutex);
		if (m_TaskQueue.size() == 0) {
			return false;
		}
		o_task = m_TaskQueue.front();
		m_TaskQueue.pop_front();
		return true;
	}

	void push_exit(unsigned int n) {
		sem.post(n);
	}


private:

	deque<function<void(void)>> m_TaskQueue;
	mutable mutex m_mutex;
	semaphore sem;
};