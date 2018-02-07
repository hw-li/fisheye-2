#include<iostream>

#include"fileio.h"

int main(int argc, char** argv) {
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << std::endl;
		loadfile(argv[i]);
		std::cout << std::endl;
	}
	int pause;
	std::cin >> pause;
	return 0;
}