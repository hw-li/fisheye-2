/*
the entrance of displaying a cubemap
*/
#include<cstdio>

#include"fileio.h"

#include"compress.h"

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

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
	
	std::FILE *inputFile;
	std::FILE *outputFile;
	fopen_s(&inputFile, "C:/Users/lanzhige/Documents/project/cubemap/build/src/Debug/40.8790234954071_-74.61353423782953_0_0_f_c.bin", "rb");
	fopen_s(&outputFile, "C:/Users/lanzhige/Documents/project/cubemap/build/src/Debug/output.bin", "wb");
	SET_BINARY_MODE(inputFile);
	SET_BINARY_MODE(outputFile);
	inf(inputFile, outputFile);

	return 0;
}