#pragma once

#include <set>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <thread>


using namespace std;

class ThreadPool
{
public:
	ThreadPool() {};
	~ThreadPool()
	{
		for (auto &it : m_Threads)
		{
			delete it.second;
		}
	};

	ThreadPool(ThreadPool const&) = delete;
	ThreadPool& operator=(ThreadPool const&) = delete;

	//is this thread in
	bool is_this_thread_in()
	{
		auto it = m_Threads.find(this_thread::get_id());
		return it != m_Threads.end();
	}

	//is thread in
	bool is_thread_in(thread* a_thread)
	{
		if (!a_thread) return false;
		auto it = m_Threads.find(a_thread->get_id());
		return it != m_Threads.end();
	}

	//create thread
	template<typename F>
	thread* create_thread(F threadfunc) 
	{
		thread  *new_thread = new thread(threadfunc);
		m_Threads[new_thread->get_id()] = new_thread;
		return new_thread;
	}

	//add thread
	void add_thread(thread* a_thread) 
	{
		if (a_thread) {
			if (is_thread_in(a_thread)) 
			{
				throw runtime_error(
					"thread_group: trying to add a duplicated thread");
			}
			m_Threads[a_thread->get_id()] = a_thread;
		}
	}

	// remove thread
	void remove_thread(thread* a_thread) 
	{
		auto it = m_Threads.find(a_thread->get_id());
		if (it != m_Threads.end())
		{
			m_Threads.erase(it);
		}
	}


	//size
	size_t size() 
	{
		return m_Threads.size();
	}

private:
	unordered_map<thread::id,thread*> m_Threads;
};