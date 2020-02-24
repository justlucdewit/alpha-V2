/*
    alpha code is a project started by luc de wit
    it was started on 12-2-2020
    
    it was originally meant to be a improvement on
    the language zettacode made by joseph catanzarit
*/

#include <iostream>
#include <vector>
#include <string>

#include "headers/validator.h"
#include "headers/readfile.h"

#define VERSION "2.1.1"

int main(int argc, char** argv)
{
    if (argc >= 2){
        std::vector<Token> tokens = lexer(readFile(argv[1]));
        validator(tokens);

        for (int i = 0; i < tokens.size(); i++){
            //tokens[i].debug();
        }

        std::cout << "done executing\n";
        
    }
    
    return 0;
}