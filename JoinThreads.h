#pragma once
#include <vector>
#include <thread>

class JoinThreads {
private:
	std::vector<std::thread> & threads;
public:
	explicit JoinThreads(std::vector<std::thread> & _threads) : threads(_threads) {}
	~JoinThreads();
};