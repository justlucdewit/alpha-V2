#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#include "tokens.h"

void validator(std::vector<Token> tokens){
    int tokenIndex = 0;

    std::map<std::string, std::vector<std::vector<Tokentype>>> argData;
    argData["debug"] = {};
    argData["more"] = {{alph_variable, alph_number}};
    argData["less"] = {{alph_variable, alph_number}};
    argData["goto"] = {{alph_variable}};
    argData["print"] = {{alph_string, alph_variable, alph_number}};
    argData["get"] = {{alph_variable}};
    argData["exit"] = {{alph_number, alph_variable}};
    argData["let"] = {{alph_variable}, {alph_string, alph_number}};

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
                std::cout << "[ERROR] :" << tokens[tokenIndex].getValue() << " is a marker, and can not have any arguments on line " << tokens[tokenIndex].getLineNumber() << "\n";
                
                exit(1);
            }
        }

        //look if command has right amounts of arguments
        if (argData[command.getValue()].size() != arguments.size()){
            std::cout << "[ERROR] wrong number of arguments on " << command.getValue() << " command on line " << command.getLineNumber() << "\n";
            std::cout << " => " << command.getValue();

            for (int i = 0; i < arguments.size(); i++){
                std::cout << " " << arguments[i].getValue();
            }

            exit(1);
        }

        for (int i = 0; i < arguments.size(); i++){
            Token arg = arguments[i];
            std::vector<Tokentype> allowedTypes = argData[command.getValue()][i];

            if (std::find(allowedTypes.begin(), allowedTypes.end(), arg.getType()) == allowedTypes.end()){
                std::cout << "[ERROR] WRONG TYPE on line " << command.getLineNumber() <<"\n";
                exit(1);
            }
        }
    }
}