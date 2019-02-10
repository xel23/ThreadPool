#include "Factorization.h"

int main(/*int argc, char * argv[]*/) {
	try {
		Factorization test;
		test.work("i.txt", "o.txt");
	}
	catch (std::exception & ex) {
		std::cout << ex.what() << std::endl;
	}
}