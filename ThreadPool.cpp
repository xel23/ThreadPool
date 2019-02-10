#include "ThreadPool.h"

void ThreadPool::workerThread()
{
	while (!done) {
		Wrapper task;
		if (workQueue.tryPop(task)) {
			task();
		}
		else {
			std::this_thread::yield();
		}
	}
}

ThreadPool::ThreadPool() : done(false), joiner(threads)
{
	for (size_t i = 0; i < threadCount;++i) {
		threads.push_back(std::thread(&ThreadPool::workerThread, this));
	}
}

ThreadPool::~ThreadPool()
{
	done = true;
}
