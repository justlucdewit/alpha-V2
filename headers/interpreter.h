#ifndef INTERPRETER_GUARD
#define INTERPRETER_GUARD 1

#include <functional>
#include <iostream>
#include <vector>
#include <map>

#include "tokens.h"
namespace alphCMDs{
    void print(std::vector<Token> arguments){
        std::cout << arguments[0].getValue() << "\n";
    }

    void exit(std::vector<Token> arguments){
        std::exit(std::atoi(arguments[0].getValue().c_str()));
    }
}

void interpretCode(std::vector<Token> tokens){
    std::map<std::string, std::function<void(std::vector<Token>)> > alph_commands;
    alph_commands["print"] = alphCMDs::print;
    alph_commands["exit"] = alphCMDs::exit;

    int tokenIndex = 0;

    while(tokenIndex < tokens.size()){
        //gather command
        Token command = tokens[tokenIndex];
        std::vector<Token> arguments;

        //gather arguments
        tokenIndex++;
        while(tokens[tokenIndex].getType() != alph_command && tokens[tokenIndex].getType() != alph_marker && tokenIndex < tokens.size()){
            arguments.push_back(tokens[tokenIndex]);
            tokenIndex++;
        }

        alph_commands[command.getValue()](arguments);
    }
}

#endif