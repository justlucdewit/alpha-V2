#include <map>
#include <string>
#include <iostream>

namespace alphaTools{
    void validateVar(std::string name, std::map<std::string, Variable> memory){
        if (memory.find(name) == memory.end()){
            std::cout << "[ERROR] variable named " << name << "was not found";
            exit(1);
        }
    }

    void validateMark(std::string name, std::map<std::string, int> markers){
        if (markers.find(name) == markers.end()){
            std::cout << "[ERROR] marker named " << name << "was not found";
            exit(1);
        }
    }
}