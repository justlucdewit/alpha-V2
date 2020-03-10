#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable>& memory, int lineNr, int& currLine, std::map<std::string, int> markers, std::vector<Token> tokens, bool& exiting

#include <iostream>
#include <vector>
#include <map>

#include "../headers/alphaTools.h"
#include "../headers/tokens.h"
#include "../headers/varsys.h"

namespace alphCMDs{
    void let(ARGUMENTS){
        struct Variable newvar;
        newvar.name = arguments[0].getValue().c_str();
        
        if (arguments[1].getType() == alph_string){
            newvar.type = alph_string;
            newvar.str_value = arguments[1].getValue();
        }else{
            newvar.type = alph_number;
            newvar.num_value = std::atoi(arguments[1].getValue().c_str());
        }

        memory[arguments[0].getValue()] = newvar;
    }
}