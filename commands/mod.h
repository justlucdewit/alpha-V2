#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable>& memory, int lineNr, int& currLine, std::map<std::string, int> markers, std::vector<Token> tokens, bool& exiting

#include <iostream>
#include <vector>
#include <map>

#include "../headers/alphaTools.h"
#include "../headers/tokens.h"
#include "../headers/varsys.h"

namespace alphCMDs{
    void mod(ARGUMENTS){
        long double value;
        if (arguments[1].getType() == alph_variable){
            Variable tmpvar = memory[arguments[1].getValue()];
            if (tmpvar.type == alph_number){
                value = tmpvar.num_value;
            }else{
                std::cout << "[ERROR] math between number and string is not allowed";
                std::exit(1);
            }
        }else{
            value = std::stold(arguments[1].getValue());
        }
        
        memory[arguments[0].getValue()].num_value = std::fmod(memory[arguments[0].getValue()].num_value, value);
    }
}