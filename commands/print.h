#ifndef PRINT
#define PRINT
#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable>& memory, int lineNr, int& currLine, std::map<std::string, int> markers, std::vector<Token> tokens, bool& exiting

#include <iostream>
#include <vector>
#include <map>

#include "../headers/alphaTools.h"
#include "../headers/tokens.h"
#include "../headers/varsys.h"

namespace alphCMDs{
    void print(ARGUMENTS){
        if (arguments[0].getType() == alph_string){
            std::cout << arguments[0].getValue();
        }else if (arguments[0].getType() == alph_variable){
            alphaTools::validateVar(arguments[0].getValue(), memory);
            Variable printedVar = memory[arguments[0].getValue()];
            if (printedVar.type == alph_number){
                std::cout << printedVar.num_value;
            }else{
                std::cout << printedVar.str_value;
            }
        }
    }
}
#endif