#pragma once
#include <mutex>
#include <queue>
#include <iostream>
#include <condition_variable>

template <class T>
class ThreadSafeQueue {
private:
	mutable std::mutex mut;
	std::queue<T> dataQueue;
	std::condition_variable dataCond;
public:
	ThreadSafeQueue() {}
	void push(T value);
	void waitAndPop(T & value);
	std::shared_ptr<T> waitAndPop();
	bool tryPop(T & value);
	std::shared_ptr<T> tryPop();
	bool empty();
	int size();
};

template<class T>
inline void ThreadSafeQueue<T>::push(T value)
{
	std::lock_guard<std::mutex> lk(mut);
	dataQueue.push(std::move(value));
	dataCond.notify_one();
}

template<class T>
inline void ThreadSafeQueue<T>::waitAndPop(T & value)
{
	std::unique_lock<std::mutex> lk(mut);
	dataCond.wait(lk, [this] {
		!dataQueue.empty();
	});
	value = std::move(dataQueue.front());
	dataQueue.pop();
}

template<class T>
inline std::shared_ptr<T> ThreadSafeQueue<T>::waitAndPop()
{
	std::unique_lock<std::mutex> lk(mut);
	dataCond.wait(lk, [this] {
		!dataQueue.empty();
	});
	std::shared_ptr<T> result(std::make_shared<T>(std::move(dataQueue.front())));
	dataQueue.pop();
	return result;
}

template<class T>
inline bool ThreadSafeQueue<T>::tryPop(T & value)
{
	std::lock_guard<std::mutex> lk(mut);
	//std::this_thread::sleep_for(std::chrono::milliseconds(15));
	if (dataQueue.empty()) return false;
	value = std::move(dataQueue.front());
	dataQueue.pop();
	return true;
}

template<class T>
inline std::shared_ptr<T> ThreadSafeQueue<T>::tryPop()
{
	std::lock_guard<std::mutex> lk(mut);
	if (dataQueue.empty()) return std::shared_ptr<T>();
	std::shared_ptr<T> result(std::make_shared<T>(std::move(dataQueue.front())));
	dataQueue.pop();
	return result;
}

template<class T>
inline bool ThreadSafeQueue<T>::empty()
{
	std::lock_guard<std::mutex> lk(mut);
	return dataQueue.empty();
}

template<class T>
inline int ThreadSafeQueue<T>::size()
{
	return dataQueue.size();
}
