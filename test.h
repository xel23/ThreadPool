#pragma once
#include "ThreadPool.h"


template<typename Iterator, typename T>
struct accumulate_block
{
	T operator()(Iterator first, Iterator last)
	{
		return std::accumulate(first, last, T());
	}
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
	unsigned long const lenngh = std::distance(first, last);

	if (!lenngh) {
		return init;
	}

	unsigned long const block_size = 25;
	unsigned long const num_blocks = (lenngh + block_size - 1) / block_size;

	std::vector<std::future<T>> futures(num_blocks - 1);

	ThreadPool pool;

	Iterator block_start = first;
	for (unsigned long i = 0; i < (num_blocks - 1);++i) {
		Iterator block_end = block_start;
		std::advance(block_end, block_size);
		futures[i] = pool.submit([block_start, block_end]()
		{
			accumulate_block<Iterator, T> a();
			return a(block_start, block_end);
		});
		block_start = block_end;
	}
	T res = init;
	return res;
}