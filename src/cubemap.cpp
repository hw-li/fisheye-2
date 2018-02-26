/*
the entrance of displaying a cubemap
*/
#include<cstdio>

#include"fileio.h"

#include"compress.h"

int main(int argc, char** argv) {

	if (argc > 1) {
		std::cout << argv[1] << std::endl;
		if (argc > 2) {
			std::cout << argv[2] << std::endl;
			loadfile(argv[1], argv[2]);
			std::cout << std::endl;
		}
		else {
			std::cout << "please input a directory to output files: ";
			string path;
			std::cin >> path;
			loadfile(argv[1], path);
		}
		
		std::cout << std::endl;
	}
	
	//std::FILE *inputFile = std::fopen("C:/Users/lanzhige/Documents/project/cubemap/buil/src/Debug/-23.4017474730932_-46.51033859574164_0_0_f_c.bin", "rb");
	//std::FILE *outputFile = std::fopen("C:/Users/lanzhige/Documents/project/cubemap/buil/src/Debug/output.bin", "wb");

	//SET_BINARY_MODE(inputFile);
	//SET_BINARY_MODE(outputFile);
	/*decomp("C:/Users/lanzhige/Documents/project/cubemap/buil/src/Debug/-23.4017474730932_-46.51033859574164_0_0_f_c.bin", "C:/Users/lanzhige/Documents/project/cubemap/buil/src/Debug/output.bin");
	int pause;
	std::cin >> pause;*/
	//inf(inputFile, outputFile);

	return 0;
}