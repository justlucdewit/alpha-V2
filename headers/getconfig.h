#include <string>
#include <iostream>
#include <fstream>

void getconfig(std::string path){
	size_t found = path.find_last_of("/\\");
	path.erase(found+1).append("acconfig.ac");
	std::cout << "executable at " << path << "\n";
}