/*
the entrance of displaying a cubemap
*/
#include<cstdio>

#include"fileio.h"

#include"compress.h"

int main(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		std::cout << argv[i] << std::endl;
		loadfile(argv[i]);
		std::cout << std::endl;
	}

	//std::FILE *inputFile = std::fopen("C:/Users/lanzhige/Documents/project/cubemap/buil/src/Debug/-23.4017474730932_-46.51033859574164_0_0_f_c.bin", "rb");
	//std::FILE *outputFile = std::fopen("C:/Users/lanzhige/Documents/project/cubemap/buil/src/Debug/output.bin", "wb");

	//SET_BINARY_MODE(inputFile);
	//SET_BINARY_MODE(outputFile);
	decomp("C:/Users/lanzhige/Documents/project/cubemap/buil/src/Debug/-23.4017474730932_-46.51033859574164_0_0_f_c.bin", "C:/Users/lanzhige/Documents/project/cubemap/buil/src/Debug/output.bin");
	int pause;
	std::cin >> pause;
	//inf(inputFile, outputFile);

	return 0;
}