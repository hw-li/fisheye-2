#pragma once

#include<experimental/filesystem>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<ctime>

#include"fisheye.h"

using std::string;
namespace fs = std::experimental::filesystem;

struct Img {
	int count;
	bool direction[6];
	Img() {
		count = 0;
		direction[0] = false;
		direction[1] = false;
		direction[2] = false;
		direction[3] = false;
		direction[4] = false;
		direction[5] = false;
	}
};

static std::unordered_map<string, int> jpg_postfix = {
	{ "_0_0.jpg", 8 },
	{ "0_90.jpg", 9 },
	{ "_270.jpg", 10 },
	{ "90_0.jpg", 9 },
	{ "80_0.jpg", 10 },
	{ "70_0.jpg",10 }
};

//CityName / TileGroups / Tiles / lat_lon_angle1_angle2.jpg
static std::unordered_map<string, int> bin_postfix = {
	{ "_0_0.bin", 8 },
	{ "0_90.bin", 9 },
	{ "_270.bin", 10 },
	{ "90_0.bin", 9 },
	{ "80_0.bin", 10 },
	{ "70_0.bin",10 }
};

static Fisheye fe;

/* recursively read directories and read image or binary files
to generate fisheye file. Para basepath is the base path of input.
Inpath is the path of the current directory. Outpath is the path
of output directory. Para op is set to output image or binary file.
*/
int recursiveLoad(const string &basepath
	, const string& inpath, const string &outpath, int op = 1) {
	fs::path filepath(inpath);
	string outDir, inDir;
	fs::path temp(outpath);
	outDir = temp.string();
	fs::path base(basepath);
	inDir = base.string();

	std::unordered_map<string, int> hmap;
	std::unordered_map<string, int> binmap;

	string curDir = filepath.string();

	string outputDir = outDir + curDir.substr(
		inDir.length(), curDir.length() - inDir.length()
	);
	fs::create_directories(outputDir);
	int res = 0;

	for (auto &dir : fs::directory_iterator(filepath)) {
		if (fs::is_directory(dir)) {
			string temp = dir.path().string();
			std::cout << "Start processing files in folder: " 
				<< temp << std::endl;
			std::clock_t start;
			double duration;
			start = std::clock();
			int count = recursiveLoad(basepath, temp, outpath, op);
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			std::cout << "Finished processing files in folder " << temp
				<< ". Time used: " << duration
				<< ". Files processed: " << count << "." << std::endl;
			continue;
		}

		string s = dir.path().string();
		// to reduce time consuming use
		// if (s.find(".bin") != string::npos) break;
		if ((op & 1)!=0&& s.find(".jpg") != string::npos) {
			if (s.length() < 8) continue;
			string name = s.substr(
				0, s.length() - jpg_postfix[s.substr(s.length() - 8, 8)]
			);
			if (hmap.find(name) != hmap.end()) {
				if (hmap[name] < 5) {
					hmap[name]++;
				}
				else if (hmap[name] > 5) {
					std::cerr << "more than 6 image of the same latlng exist: "
						<< name << std::endl;
				}
				else {
					string out = outputDir + name.substr(
						curDir.length(), name.length() - curDir.length()
					) + "_f.png";
					fe.draw(name, out, 1);
					hmap[name]++;
				}
			}
			else {
				hmap[name] = 1;
			}
			res++;
		}
		if ((op & 2) != 0 && s.find(".bin") != string::npos) {
			if (s.length() < 8) continue;
			string name = s.substr(
				0, s.length() - bin_postfix[s.substr(s.length() - 8, 8)]
			);
			if (binmap.find(name) != binmap.end()) {
				if (binmap[name] < 5) {
					binmap[name]++;
				}
				else if (binmap[name] > 5) {
					std::cerr << "more than 6 image of the same latlng exist: "
						<< name << std::endl;
				}
				else {
					string out = outputDir + name.substr(
						curDir.length(), name.length() - curDir.length()
					);
					fe.draw(name, out, 2);
					binmap[name]++;
				}
			}
			else {
				binmap[name] = 1;
			}
			res++;
		}
	}
	return res;
}