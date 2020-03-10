#ifndef ALPHATOOLS
#define ALPHATOOLS

#include <map>
#include <string>
#include <iostream>

#include "./varsys.h"

namespace alphaTools{
    void validateVar(std::string name, std::map<std::string, Variable> memory){
        if (memory.find(name) == memory.end()){
            std::cout << "[ERROR] variable named " << name << " was not found";
            exit(1);
        }
    }

    void validateMark(std::string name, std::map<std::string, int> markers){
        if (markers.find(name) == markers.end()){
            std::cout << "[ERROR] marker named " << name << " was not found";
            exit(1);
        }
    }

    int getTokenIndex(int line, std::vector<Token> tokens){
        int linesfound = 0;
        for (int i = 0; i <= tokens.size(); i++){
            Token currtoken = tokens[i];
            if (currtoken.getType() == alph_command){
                linesfound++;
                if (i == line){
                    return i;
                }
            }
        }
    }
}

#endif