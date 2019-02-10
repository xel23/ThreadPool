#include "Factorization.h"
#include <iostream>

void Factorization::factorization(uint64_t num, uint64_t generalNum)
{
	//std::cout << std::this_thread::get_id() << std::endl;
	// Fermat's factorization method
	if (num % 2 == 1) {
		uint64_t s = (uint64_t)sqrt(num);
		bool flag = false;
		while (s < num) {
			uint64_t y = (uint64_t)sqrt(s*s - num);
			if (num == (s*s - y*y) && (s - y != 1)) {
				factorization(s - y, generalNum);
				factorization(s + y, generalNum);
				flag = true;
				break;
			}
			s++;
		}
		if (!flag && num != 1) {
			storage[generalNum].push_back(num);
		}
	}
	else {
		storage[generalNum].push_back(2);
		factorization(num / 2, generalNum);
	}
	//return cur;
}

std::string Factorization::printStringN(uint64_t N)
{
	std::string res = "";
	for (size_t i = 0; i < storage[N].size(); i++) {
		if (i != storage[N].size() - 1) res += storage[N][i] + "*";
		else res += std::to_string(storage[N][i]);
	}
	std::cout << res << std::endl;
	return res;
}

void Factorization::printInFile(std::ofstream & output, uint64_t N)
{
	output << "Factoriazation of " << N << " = ";
	for (size_t i = 0; i < storage[N].size(); i++) {
		if (i != storage[N].size() - 1) output << storage[N][i] << "*";
		else output << storage[N][i];
	}
	output << std::endl;
}

void Factorization::work(const std::string & inputFilename, const std::string & outputFilename)
{
	std::ifstream input(inputFilename, std::ios::in);
	std::ofstream output(outputFilename, std::ios::out);
	if (!input.is_open()) throw FileNotFound("File " + inputFilename + " not found");
	if (!output.is_open()) throw FileNotFound("File " + outputFilename + " can't open");
	std::map<uint64_t, std::future <void>> getter;
	std::vector<uint64_t> ttt;
	while (!input.eof()) {
		uint64_t N;
		input >> N;
		ttt.emplace_back(N);
		getter[N] = pool.submit([this, N]() {
			factorization(N, N);
		});

	}
	size_t size = ttt.size();
	for (size_t i = 0; i < size; ++i) {
		getter[ttt[i]].get();
		printInFile(output, ttt[i]);
	}
	input.close();
	output.close();
}

/*void Factorization::getNumber(const std::string & filename)
{
	std::ifstream input(filename);
	if (!input.is_open()) throw FileNotFound("File " + filename + " not found");
	while (!input.eof()) {
		std::string line;
		std::getline(input, line);
		std::istringstream tmp(line);
		uint64_t N;
		uint64_t res = 1;
		while (tmp >> N) {
			res *= N;
		}
		std::cout << res << std::endl;
	}
}

void Factorization::addInStorage(uint64_t N)
{
	storage[N] = cur;
	cur.clear();
}*/