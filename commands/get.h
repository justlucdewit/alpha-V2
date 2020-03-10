#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable>& memory, int lineNr, int& currLine, std::map<std::string, int> markers, std::vector<Token> tokens

#include <iostream>
#include <vector>
#include <map>

#include "../headers/alphaTools.h"
#include "../headers/tokens.h"
#include "../headers/varsys.h"

namespace alphCMDs{
    void get(ARGUMENTS){
        Variable value;
        value.type = alph_string;
        std::cin >> value.str_value;
        memory[arguments[0].getValue()] = value;
    }
}