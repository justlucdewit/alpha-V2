#ifndef INTERPRETER_GUARD
#define INTERPRETER_GUARD 1

#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable>& memory, int lineNr, int& currLine, std::map<std::string, int> markers

#include <functional>
#include <iostream>
#include <vector>
#include <map>

#include "varsys.h"
#include "tokens.h"

namespace alphCMDs{
    void print(ARGUMENTS){
        if (arguments[0].getType() == alph_string){
            std::cout << arguments[0].getValue() << "\n";
        }else if (arguments[0].getType() == alph_variable){
            Variable printedVar = memory[arguments[0].getValue()];
            if (printedVar.type == alph_number){
                std::cout << printedVar.num_value << "\n";
            }else{
                std::cout << printedVar.str_value << "\n";
            }
        }
    }

    void exit(ARGUMENTS){
        std::exit(std::atoi(arguments[0].getValue().c_str()));
    }

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

    void debug(ARGUMENTS){
        std::map<std::string, int>::iterator it;

        for (auto it = memory.begin(); it != memory.end(); it++ )
        {   
            if (it->second.type == alph_number){
                std::cout << it->first << " = " << it->second.num_value << "\n";
            }else{
                std::cout << it->first << " = \"" << it->second.str_value << "\"\n";
            }
        }
    }


    void more(ARGUMENTS){
        Variable thevar = memory[arguments[0].getValue()];
        if (thevar.type == alph_number){
            thevar.num_value++;
            memory[arguments[0].getValue()] = thevar;
        }else{
            std::cout << "[ERROR] triend incrementing string variable on line " << lineNr;
            std::exit(1);
        }
    }

    void less(ARGUMENTS){
        Variable thevar = memory[arguments[0].getValue()];
        if (thevar.type == alph_number){
            thevar.num_value--;
            memory[arguments[0].getValue()] = thevar;
        }else{
            std::cout << "[ERROR] triend decrementing string variable on line " << lineNr;
            std::exit(1);
        }
    }
    
    void alph_goto(ARGUMENTS){
        currLine = markers[arguments[0].getValue()];
    }

    void get(ARGUMENTS){

    }
}

void interpretCode(std::vector<Token> tokens){
    //create a map to store what functions to call on what command
    std::map<std::string, int> markers;
    std::map<std::string, Variable> memory;
    std::map<std::string, std::function<void(std::vector<Token>, std::map<std::string, Variable>&, int, int&, std::map<std::string, int>)> > alph_commands;
    alph_commands["print"] = alphCMDs::print;
    alph_commands["exit"] = alphCMDs::exit;
    alph_commands["let"] = alphCMDs::let;
    alph_commands["goto"] = alphCMDs::alph_goto;
    alph_commands["more"] = alphCMDs::more;
    alph_commands["less"] = alphCMDs::less;
    alph_commands["get"] = alphCMDs::get;
    alph_commands["debug"] = alphCMDs::debug;

    //main program loop
    int tokenIndex = 0;
    while(tokenIndex < tokens.size()){
        //gather command
        Token command = tokens[tokenIndex];
        std::vector<Token> arguments;

        if (command.getType() == alph_marker){
            markers[command.getValue()] = command.getLineNumber();
            tokenIndex++;
            continue;
        }

        //gather arguments
        tokenIndex++;
        while(tokens[tokenIndex].getType() != alph_command && tokens[tokenIndex].getType() != alph_marker && tokenIndex < tokens.size()){
            arguments.push_back(tokens[tokenIndex]);
            tokenIndex++;
        }


        alph_commands[command.getValue()](arguments, memory, command.getLineNumber(), tokenIndex, markers);
    }
}

#endif