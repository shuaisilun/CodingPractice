#pragma once
#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <mutex>
#include <atomic>
#include <condition_variable>
using namespace std;

class semaphore {
public:
	explicit semaphore(unsigned int initial = 0) {
#if defined(HAVE_SEM)
		sem_init(&sem, 0, initial);
#else
		count_ = 0;
#endif
	}
	~semaphore() {
#if defined(HAVE_SEM)
		sem_destroy(&sem);
#endif
	}
	void post(unsigned int n = 1) {
#if defined(HAVE_SEM)
		while (n--) {
			sem_post(&sem);
		}
#else
		unique_lock<mutex> lock(mutex_);
		count_ += n;
		while (n--) {
			condition_.notify_one();
		}
#endif

	}
	void wait() {
#if defined(HAVE_SEM)
		sem_wait(&sem);
#else
		unique_lock<mutex> lock(mutex_);
		while (count_ == 0) {
			condition_.wait(lock);
		}
		--count_;
#endif
	}
private:
#if defined(HAVE_SEM)
	sem_t sem;
#else
	atomic_uint count_;
	mutex mutex_;
	condition_variable_any condition_;
#endif
}; 

#endif /* SEMAPHORE_H_ */