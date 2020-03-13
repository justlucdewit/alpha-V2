#ifndef READFILE_GUARD
#define READFILE_GUARD 1
#include <iostream>
#include <fstream>

std::string readFile(const char* filename, const char* errorMsg){
    std::ifstream ifs(filename);

    if (!ifs.is_open()){
        std::cout << "[ERROR] " << filename << " " << errorMsg;
        std::exit(1);
    }
    std::string content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
    return content;
}

#endif