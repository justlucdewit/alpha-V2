#ifndef INTERPRETER_GUARD
#define INTERPRETER_GUARD 1

#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable>& memory, int lineNr, int& currLine, std::map<std::string, int> markers, std::vector<Token> tokens, bool& exiting

#include <functional>
#include <iostream>
#include <variant>
#include <vector>
#include <cmath>
#include <map>

#include "alphaTools.h"
#include "varsys.h"
#include "tokens.h"

void interpretCode(std::vector<Token> tokens, std::map<std::string, int> markers, std::map<std::string, std::function<void(std::vector<Token>, std::map<std::string, Variable>&, int, int&, std::map<std::string, int>, std::vector<Token>, bool&)> > alph_commands){
    bool exiting = false;

    //create a map to store what functions to call on what command
    std::map<std::string, Variable> memory;

    //std::cout << "got " << markers.size() << " markers, first one is at line " << alphaTools::getTokenIndex(markers["loop"], tokens) << "\n";

    //main program loop
    int tokenIndex = 0;
    while(tokenIndex < tokens.size() && !exiting){
        //gather command
        Token command = tokens[tokenIndex];
        //std::cout << "now at command: " << command.getValue() << "\n";
        std::vector<Token> arguments;

        //gather arguments
        tokenIndex++;
        while(tokens[tokenIndex].getType() != alph_command && tokens[tokenIndex].getType() != alph_marker && tokenIndex < tokens.size()){
            arguments.push_back(tokens[tokenIndex]);
            tokenIndex++;
        }

        alph_commands[command.getValue()](arguments, memory, command.getLineNumber(), tokenIndex, markers, tokens, exiting);
    }

    return;
}
#endif