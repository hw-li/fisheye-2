#pragma once

#include<experimental/filesystem>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>

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

int loadfile(const string &filepath) {
	//std::unordered_map<string, Img> hmap;
	// if the images in the folder will not be duplicated,
	// we can use the hmap as follow:
	std::unordered_map<string, int> hmap;
	const std::unordered_map<string, int> postfix = { {"_0_0.jpg", 8} };
	int count = 0;
	std::stringstream ss;
	for (auto & name : fs::directory_iterator(filepath)) {
		ss << name << std::endl;
		//std::cout << name << std::endl;
		count++;
	}
	for (int i = 0; i < count; i++) {
		string s;
		ss >> s;
		std::cout << s << std::endl;
	}
	return 0;
}