#ifndef READFILE_GUARD
#define READFILE_GUARD 1
#include <iostream>
#include <fstream>

std::string readFile(char* filename){
    std::ifstream ifs(filename);
    std::string content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
    return content;
}

#endif