#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable>& memory, int lineNr, int& currLine, std::map<std::string, int> markers, std::vector<Token> tokens, bool& exiting

#include <iostream>
#include <vector>
#include <map>

#include "../headers/alphaTools.h"
#include "../headers/tokens.h"
#include "../headers/varsys.h"

namespace alphCMDs{
    void less(ARGUMENTS){
        alphaTools::validateVar(arguments[0].getValue(), memory);
        Variable thevar = memory[arguments[0].getValue()];

        if (thevar.type == alph_number){
            thevar.num_value--;
            memory[arguments[0].getValue()] = thevar;
        }else{
            std::cout << "[ERROR] triend decrementing string variable on line " << lineNr;
            std::exit(1);
        }
    }
}