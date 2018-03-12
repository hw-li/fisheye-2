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
		if (argc > 3) {
			recursiveLoad(argv[2], argv[2], argv[3], 2);
		}
		else if (argc > 2) {
			std::cout << argv[2] << std::endl;
			recursiveLoad(argv[1], argv[1], argv[2], 1);
			std::cout << std::endl;
		}
		else {
			std::cout << "please input a directory to output files: ";
			string path;
			std::cin >> path;
			recursiveLoad(argv[1],argv[1], path);
		}
		
		std::cout << std::endl;
	}
	return 0;
}