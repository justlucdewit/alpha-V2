#ifndef INTERPRETER_GUARD
#define INTERPRETER_GUARD 1

#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable> memory

#include <functional>
#include <iostream>
#include <vector>
#include <map>

#include "varsys.h"
#include "tokens.h"

namespace alphCMDs{
    void print(ARGUMENTS){
        std::cout << arguments[0].getValue() << "\n";
    }

    void exit(ARGUMENTS){
        std::exit(std::atoi(arguments[0].getValue().c_str()));
    }

    void let(ARGUMENTS){
        struct Variable newvar;
        newvar.name = arguments[0].getValue().c_str();
        
        if (arguments[1].getType() == alph_string){
            newvar.type = alph_string;
            newvar.str_value = arguments[1].getValue().c_str();
        }else{
            newvar.type = alph_number;
            newvar.num_value = std::atoi(arguments[1].getValue().c_str());
        }

        memory[arguments[0].getValue()] = newvar;
        std::cout << "memory size in func: " << memory.size() << "\n";
    }

    void debug(ARGUMENTS){
        for (auto it = memory.begin(); it != memory.end(); ++it)
        {
            std::cout << "yesy";
            std::cout << it->first;
        }
    }

    void alph_goto(ARGUMENTS){

    }

    void more(ARGUMENTS){

    }

    void less(ARGUMENTS){

    }

    void get(ARGUMENTS){

    }
}

void interpretCode(std::vector<Token> tokens){
    std::map<std::string, Variable> memory;

    std::map<std::string, std::function<void(std::vector<Token>, std::map<std::string, Variable>)> > alph_commands;
    alph_commands["print"] = alphCMDs::print;
    alph_commands["exit"] = alphCMDs::exit;
    alph_commands["let"] = alphCMDs::let;
    alph_commands["goto"] = alphCMDs::alph_goto;
    alph_commands["more"] = alphCMDs::more;
    alph_commands["less"] = alphCMDs::less;
    alph_commands["get"] = alphCMDs::get;
    alph_commands["debug"] = alphCMDs::debug;

    int tokenIndex = 0;
    

    while(tokenIndex < tokens.size()){
        std::cout << "memsize: " << memory.size() << '\n';
        //gather command
        Token command = tokens[tokenIndex];
        std::vector<Token> arguments;

        //gather arguments
        tokenIndex++;
        while(tokens[tokenIndex].getType() != alph_command && tokens[tokenIndex].getType() != alph_marker && tokenIndex < tokens.size()){
            arguments.push_back(tokens[tokenIndex]);
            tokenIndex++;
        }

        alph_commands[command.getValue()](arguments, memory);
    }
}

#endif