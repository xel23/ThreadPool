#pragma once
#include <thread>
#include <atomic>
#include <vector>
#include <iostream>
#include <future>

#include "ThreadSafeQueue.h"
#include "JoinThreads.h"
#include "Wrapper.h"


class ThreadPool {
private:
	std::atomic_bool done;
	ThreadSafeQueue<Wrapper> workQueue;
	std::vector<std::thread> threads;
	unsigned const threadCount = std::thread::hardware_concurrency();
	JoinThreads joiner;

	void workerThread();
public:
	ThreadPool();
	~ThreadPool();

	template <class FunctionType>
	std::future<typename std::result_of<FunctionType()>::type> submit(FunctionType f) {
		typedef typename std::result_of<FunctionType()>::type resultType;
		std::packaged_task<resultType()> task(std::move(f));
		std::future<resultType> res(task.get_future());
		workQueue.push(std::move(task));
		return res;
	}
};