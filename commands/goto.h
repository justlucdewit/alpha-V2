#ifndef GOTO
#define GOTO
#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable>& memory, int lineNr, int& currLine, std::map<std::string, int> markers, std::vector<Token> tokens, bool& exiting

#include <iostream>
#include <vector>
#include <map>

#include "../headers/alphaTools.h"
#include "../headers/tokens.h"
#include "../headers/varsys.h"

namespace alphCMDs{
    void alph_goto(ARGUMENTS){
        alphaTools::validateMark(arguments[0].getValue(), markers);
        currLine = alphaTools::getTokenIndex(markers[arguments[0].getValue()], tokens);
    }
}
#endif