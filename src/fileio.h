#pragma once

#include<experimental/filesystem>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>

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
/*
int loadfile(const string &filepath, const string &outpath) {
	//std::unordered_map<string, Img> hmap;
	// if the images in the folder will not be duplicated,
	// we can use the hmap as follow:
	std::unordered_map<string, int> hmap;
	std::unordered_map<string, int> postfix = {
		{"_0_0.jpg", 8},
		{"0_90.jpg", 9}, 
		{"_270.jpg", 10},
		{"90_0.jpg", 9},
		{"80_0.jpg", 10},
		{"70_0.jpg",10}
	};
	/*std::unordered_map<string, int> postfix = {
		{"_0_0.bin", 8},
		{"0_90.bin", 9},
		{"_270.bin", 10},
		{"90_0.bin", 9},
		{"80_0.bin", 10},
		{"70_0.bin",10}
	};*/
/*	int count = 0;
	std::stringstream ss;
	for (auto & name : fs::recursive_directory_iterator(filepath)) {
		ss << name << std::endl;
		std::cout << name.path() << std::endl;
		//std::cout << name << std::endl;
		count++;
	}
	Fisheye fe;
	for (int i = 0; i < count; i++) {
		string s;
		ss >> s;
		if (s.length() < 8) continue;
		string name = 
				s.substr(0, s.length() - postfix[s.substr(s.length() - 8, 8)]);
		if (hmap.find(name) != hmap.end()) {
			if (hmap[name] < 5) {
				hmap[name]++;
			} else if (hmap[name] > 5) {
				std::cerr << "more than 6 image of the same latlng exist! error latlng: "
					<< name << std::endl;
			} else {
				std::cout << "the file name is : " << std::endl;
				fe.draw(name, outpath);
				hmap[name]++;
			}
		} else {
			hmap[name] = 1;
		}
	}
	return 0;
}*/

int loadfile(const string &inpath, const string &outpath) {
	//std::unordered_map<string, Img> hmap;
	// if the images in the folder will not be duplicated,
	// we can use the hmap as follow:
	std::unordered_map<string, int> hmap;
	std::unordered_map<string, int> postfix = {
		{ "_0_0.jpg", 8 },
		{ "0_90.jpg", 9 },
		{ "_270.jpg", 10 },
		{ "90_0.jpg", 9 },
		{ "80_0.jpg", 10 },
		{ "70_0.jpg",10 }
	};

	//CityName / TileGroups / Tiles / lat_lon_angle1_angle2.jpg
	/*std::unordered_map<string, int> postfix = {
	{"_0_0.bin", 8},
	{"0_90.bin", 9},
	{"_270.bin", 10},
	{"90_0.bin", 9},
	{"80_0.bin", 10},
	{"70_0.bin",10}
	};*/

	string outDir ,inDir;
	fs::path temp(outpath);
	outDir = temp.string();
	fs::path filepath(inpath);
	inDir = filepath.string();
	Fisheye fe;
	for (auto &tileGroups : fs::directory_iterator(filepath)) {
		for (auto &tile : fs::directory_iterator(tileGroups.path())) {
			if (!fs::is_directory(tile)) continue;
			int count = 0;
			std::stringstream ss;
			for (auto & name : fs::directory_iterator(tile.path())) {
				ss << name << std::endl;
				//std::cout << name << std::endl;
				count++;
			}

			string currentDir = tile.path().string();

			string outputDir = outDir + currentDir.substr(inDir.length(), currentDir.length()-inDir.length());
			fs::create_directories(outputDir);

			for (int i = 0; i < count; i++) {
				string s;
				ss >> s;
				// to reduce time consuming use
				// if (s.find(".bin") != string::npos) break;
				if (s.find(".jpg")==string::npos) continue;
				if (s.length() < 8) continue;
				string name =
					s.substr(0, s.length() - postfix[s.substr(s.length() - 8, 8)]);
				if (hmap.find(name) != hmap.end()) {
					if (hmap[name] < 5) {
						hmap[name]++;
					}
					else if (hmap[name] > 5) {
						std::cerr << "more than 6 image of the same latlng exist! error latlng: "
							<< name << std::endl;
					}
					else {
						string out = outputDir + name.substr(currentDir.length(), name.length() - currentDir.length()) + "_f.png";
						fe.draw(name, out);
						hmap[name]++;
					}
				}
				else {
					hmap[name] = 1;
				}
			}
		}
	}

	
	return 0;
}