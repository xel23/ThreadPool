#pragma once
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include "ExceptionList.h"
#include "ThreadPool.h"


class Factorization {
private:
	ThreadPool pool;
	std::map <uint64_t, std::vector <uint64_t> > storage;
	//std::vector <uint64_t> cur;
	//int curN;
	//std::string out;
	//void addInStorage(uint64_t N);
public:
	Factorization() {};
	~Factorization() {};
	void factorization(uint64_t num, uint64_t generalNum); //generalNum is used for similar adding in the same place
	std::string printStringN(uint64_t N);
	void printInFile(std::ofstream & output, uint64_t N);
	void work(const std::string & inputFilename, const std::string & outputFilename);
	//void getNumber(const std::string & filename);
};