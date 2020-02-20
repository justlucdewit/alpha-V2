#include <iostream>
#include <vector>
#include <string>

#include "headers/tokens.h"
#include "headers/readfile.h"

int main(int argc, char** argv)
{
    if (argc >= 2){
        std::vector<Token> tokens = lexer(readFile(argv[1]));

        for (int i = 0; i < tokens.size(); i++){
            tokens[i].debug();
        }
    }
    
    return 0;
}