#include <string>
#include <iostream>
#include <fstream>

#include "json.h"
#include "readfile.h"

std::string getconfig(std::string path){
	//get acconfig.json's path
	size_t found = path.find_last_of("/\\");
	path.erase(found+1).append("acconfig.json");

	//read file content of acconfig and parse to json
	return readFile(path.c_str(), "could not be opened, did u make a acconfig.json file?");
}