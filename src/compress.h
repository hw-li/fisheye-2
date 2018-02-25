#ifndef  COMPRESS_H_
#define COMPRESS_H_

#include<fstream>
#include<sstream>
#include<string>
#include<assert.h>
#include "zlib-1.2.11/zlib.h"

#define CHUNK 16384

using std::string;
using std::ifstream;
using std::stringstream;

int decomp(const string &inputPath, const string &outputPath) {
	int ret;
	unsigned have;
	z_stream strm;
	unsigned char *input = new unsigned char[CHUNK];
	
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	ret = inflateInit(&strm);
	if (ret != Z_OK)
		return ret;

	ifstream inputFile(inputPath, ios::in);
	ofstream outputFile(outputPath, ios::out | ios::binary);

	int len = 0;
	stringstream ss;
	if (!inputFile.is_open()) {
		std::cout<<"can't open file"<<std::endl;
		throw(std::exception("can't open file"));
	}
	ss << inputFile.rdbuf();
	vector<unsigned char> in;
	unsigned char temp;
	while (ss >> temp) {
		in.push_back(temp);
		if (ss.peek() == ',')
			ss.ignore();
	}
	std::cout << "the data: " << std::endl;
	for (int i = 0; i < in.size(); i++)
		std::cout << (int)in[i] << " " << std::endl;

	return 0;
}

int inf(FILE *source, FILE *dest) {
	int ret;
	unsigned have;
	z_stream strm;
	unsigned char *in = new unsigned char[CHUNK];
	unsigned char *out = new unsigned char[CHUNK];

	/* allocate inflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	ret = inflateInit(&strm);
	if (ret != Z_OK)
		return ret;

	/* decompress until deflate stream ends or end of file */
	do {
		strm.avail_in = fread(in, 1, CHUNK, source);
		if (ferror(source)) {
			(void)inflateEnd(&strm);
			return Z_ERRNO;
		}
		if (strm.avail_in == 0)
			break;
		strm.next_in = in;

		/* run inflate() on input until output buffer not full */
		do {
			strm.avail_out = CHUNK;
			strm.next_out = out;
			ret = inflate(&strm, Z_NO_FLUSH);
			assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
			switch (ret) {
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;     /* and fall through */
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
				(void)inflateEnd(&strm);
				return ret;
			}
			have = CHUNK - strm.avail_out;
			if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
				(void)inflateEnd(&strm);
				return Z_ERRNO;
			}
		} while (strm.avail_out == 0);

		/* done when inflate() says it's done */
	} while (ret != Z_STREAM_END);

	/* clean up and return */
	(void)inflateEnd(&strm);
	return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

/* report a zlib or i/o error */
void zerr(int ret)
{
	fputs("zpipe: ", stderr);
	switch (ret) {
	case Z_ERRNO:
		if (ferror(stdin))
			fputs("error reading stdin\n", stderr);
		if (ferror(stdout))
			fputs("error writing stdout\n", stderr);
		break;
	case Z_STREAM_ERROR:
		fputs("invalid compression level\n", stderr);
		break;
	case Z_DATA_ERROR:
		fputs("invalid or incomplete deflate data\n", stderr);
		break;
	case Z_MEM_ERROR:
		fputs("out of memory\n", stderr);
		break;
	case Z_VERSION_ERROR:
		fputs("zlib version mismatch!\n", stderr);
	}
}

#endif // ! COMPRESS_H_
