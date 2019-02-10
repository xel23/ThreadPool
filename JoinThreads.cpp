#include "JoinThreads.h"

JoinThreads::~JoinThreads()
{
	size_t count = threads.size();
	for (size_t i = 0; i < count; ++i) {
		if (threads[i].joinable()) threads[i].join();
	}
}
