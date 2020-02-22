#include <iostream>
#include <vector>
#include <map>

#include "tokens.h"

void validator(std::vector<Token> tokens){
    int tokenIndex = 0;

    std::map<std::string, int> numberOfArgsNeeded;
    numberOfArgsNeeded["debug"] = 0;
    numberOfArgsNeeded["more"] = 1;
    numberOfArgsNeeded["less"] = 1;
    numberOfArgsNeeded["goto"] = 1;
    numberOfArgsNeeded["print"] = 1;
    numberOfArgsNeeded["get"] = 1;
    numberOfArgsNeeded["exit"] = 1;
    numberOfArgsNeeded["let"] = 2;

    while(tokenIndex < tokens.size()){
        //get command
        Token command = tokens[tokenIndex];
        std::vector<Token> arguments;
        tokenIndex++;
        
        while(tokens[tokenIndex].getType() != alph_command && tokens[tokenIndex].getType() != alph_marker && tokenIndex < tokens.size()){
            arguments.push_back(tokens[tokenIndex]);
            tokenIndex++;
        }

        //get command arguments
        if (tokens[tokenIndex].getType() == alph_marker){
            if (tokens[tokenIndex+1].getType() != alph_command && tokens[tokenIndex+1].getType() != alph_marker){
                std::cout << "[ERROR] wrong number of arguments on " << command.getValue() << " command\n";
                exit(1);
            }
            tokenIndex-= 1;
        }

        //look if command has right amounts of arguments
        if (numberOfArgsNeeded[command.getValue()] != arguments.size()){
            std::cout << "[ERROR] wrong number of arguments on " << command.getValue() << " command on line " << command.getLineNumber() << "\n";
            std::cout << " => " << command.getValue();

            for (int i = 0; i < arguments.size(); i++){
                std::cout << " " << arguments[i].getValue();
            }

            exit(1);
        }
    }
}