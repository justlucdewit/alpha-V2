#ifndef INTERPRETER_GUARD
#define INTERPRETER_GUARD 1

#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable>& memory, int lineNr, int& currLine, std::map<std::string, int> markers, std::vector<Token> tokens

#include <functional>
#include <iostream>
#include <variant>
#include <vector>
#include <cmath>
#include <map>

#include "alphaTools.h"
#include "varsys.h"
#include "tokens.h"

namespace alphCMDs{
    void print(ARGUMENTS){
        if (arguments[0].getType() == alph_string){
            std::cout << arguments[0].getValue();
        }else if (arguments[0].getType() == alph_variable){
            alphaTools::validateVar(arguments[0].getValue(), memory);
            Variable printedVar = memory[arguments[0].getValue()];
            if (printedVar.type == alph_number){
                std::cout << printedVar.num_value;
            }else{
                std::cout << printedVar.str_value;
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
        alphaTools::validateVar(arguments[0].getValue(), memory);
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
    
    void alph_goto(ARGUMENTS){
        alphaTools::validateMark(arguments[0].getValue(), markers);
        currLine = alphaTools::getTokenIndex(markers[arguments[0].getValue()], tokens);
    }

    void get(ARGUMENTS){
        Variable value;
        value.type = alph_string;
        std::cin >> value.str_value;
        memory[arguments[0].getValue()] = value;
    }

    void gotoifis(ARGUMENTS){
        std::variant<int, std::string> value1, value2;
        alphaTools::validateMark(arguments[2].getValue(), markers);

        if (arguments[0].getType() == alph_variable){
            Variable tmpvar = memory[arguments[0].getValue()];
            if (tmpvar.type == alph_string){
                value1 = tmpvar.str_value;
            }else{
                value1 = tmpvar.num_value;
            }
        }else if(arguments[0].getType() == alph_number){
            value1 = std::stoi(arguments[0].getValue());
        }else{//alph_string
            value1 = arguments[0].getValue();
        }

        if (arguments[1].getType() == alph_variable){
            Variable tmpvar = memory[arguments[1].getValue()];
            if (tmpvar.type == alph_string){
                value2 = tmpvar.str_value;
            }else{
                value2 = tmpvar.num_value;
            }
        }else if(arguments[1].getType() == alph_number){
            value2 = std::stoi(arguments[1].getValue());
        }else{//alph_string
            value2 = arguments[1].getValue();
        }

        if (value1 == value2){
            currLine = alphaTools::getTokenIndex(markers[arguments[2].getValue()], tokens);
        }
    }

    void gotoifisnt(ARGUMENTS){
        std::variant<int, std::string> value1, value2;
        alphaTools::validateMark(arguments[2].getValue(), markers);

        if (arguments[0].getType() == alph_variable){
            Variable tmpvar = memory[arguments[0].getValue()];
            if (tmpvar.type == alph_string){
                value1 = tmpvar.str_value;
            }else{
                value1 = tmpvar.num_value;
            }
        }else if(arguments[0].getType() == alph_number){
            value1 = std::stoi(arguments[0].getValue());
        }else{//alph_string
            value1 = arguments[0].getValue();
        }

        if (arguments[1].getType() == alph_variable){
            Variable tmpvar = memory[arguments[1].getValue()];
            if (tmpvar.type == alph_string){
                value2 = tmpvar.str_value;
            }else{
                value2 = tmpvar.num_value;
            }
        }else if(arguments[1].getType() == alph_number){
            value2 = std::stoi(arguments[1].getValue());
        }else{//alph_string
            value2 = arguments[1].getValue();
        }

        if (value1 != value2){
            currLine = alphaTools::getTokenIndex(markers[arguments[2].getValue()], tokens);
        }
    }

    void add(ARGUMENTS){
        long double value;
        if (arguments[1].getType() == alph_variable){
            Variable tmpvar = memory[arguments[1].getValue()];
            if (tmpvar.type == alph_number){
                value = tmpvar.num_value;
            }else{
                std::cout << "[ERROR] math between number and string is not allowed";
                std::exit(1);
            }
        }else{
            value = std::stoi(arguments[1].getValue());
        }

        memory[arguments[0].getValue()].num_value += value;
    }

    void sub(ARGUMENTS){
        long double value;
        if (arguments[1].getType() == alph_variable){
            Variable tmpvar = memory[arguments[1].getValue()];
            if (tmpvar.type == alph_number){
                value = tmpvar.num_value;
            }else{
                std::cout << "[ERROR] math between number and string is not allowed";
                std::exit(1);
            }
        }else{
            value = std::stoi(arguments[1].getValue());
        }
        
        memory[arguments[0].getValue()].num_value -= value;
    }

    void mul(ARGUMENTS){
        long double value;
        if (arguments[1].getType() == alph_variable){
            Variable tmpvar = memory[arguments[1].getValue()];
            if (tmpvar.type == alph_number){
                value = tmpvar.num_value;
            }else{
                std::cout << "[ERROR] math between number and string is not allowed";
                std::exit(1);
            }
        }else{
            value = std::stoi(arguments[1].getValue());
        }
        
        memory[arguments[0].getValue()].num_value *= value;
    }

    void div(ARGUMENTS){
        long double value;
        if (arguments[1].getType() == alph_variable){
            Variable tmpvar = memory[arguments[1].getValue()];
            if (tmpvar.type == alph_number){
                value = tmpvar.num_value;
            }else{
                std::cout << "[ERROR] math between number and string is not allowed";
                std::exit(1);
            }
        }else{
            value = std::stoi(arguments[1].getValue());
        }
        
        memory[arguments[0].getValue()].num_value /= value;
    }

    void pow(ARGUMENTS){
        long double value;
        if (arguments[1].getType() == alph_variable){
            Variable tmpvar = memory[arguments[1].getValue()];
            if (tmpvar.type == alph_number){
                value = tmpvar.num_value;
            }else{
                std::cout << "[ERROR] math between number and string is not allowed";
                std::exit(1);
            }
        }else{
            value = std::stoi(arguments[1].getValue());
        }
        
        memory[arguments[0].getValue()].num_value = std::pow(memory[arguments[0].getValue()].num_value, value);
    }

    void mod(ARGUMENTS){
        long double value;
        if (arguments[1].getType() == alph_variable){
            Variable tmpvar = memory[arguments[1].getValue()];
            if (tmpvar.type == alph_number){
                value = tmpvar.num_value;
            }else{
                std::cout << "[ERROR] math between number and string is not allowed";
                std::exit(1);
            }
        }else{
            value = std::stoi(arguments[1].getValue());
        }
        
        memory[arguments[0].getValue()].num_value = std::fmod(memory[arguments[0].getValue()].num_value, value);
    }

    void gotoifislss(ARGUMENTS){
        std::variant<int, std::string> value1, value2;
        alphaTools::validateMark(arguments[2].getValue(), markers);

        if (arguments[0].getType() == alph_variable){
            Variable tmpvar = memory[arguments[0].getValue()];
            if (tmpvar.type == alph_string){
                value1 = tmpvar.str_value;
            }else{
                value1 = tmpvar.num_value;
            }
        }else if(arguments[0].getType() == alph_number){
            value1 = std::stoi(arguments[0].getValue());
        }else{//alph_string
            value1 = arguments[0].getValue();
        }

        if (arguments[1].getType() == alph_variable){
            Variable tmpvar = memory[arguments[1].getValue()];
            if (tmpvar.type == alph_string){
                value2 = tmpvar.str_value;
            }else{
                value2 = tmpvar.num_value;
            }
        }else if(arguments[1].getType() == alph_number){
            value2 = std::stoi(arguments[1].getValue());
        }else{//alph_string
            value2 = arguments[1].getValue();
        }

        if (value1 < value2){
            currLine = alphaTools::getTokenIndex(markers[arguments[2].getValue()], tokens);
        }
    }

    void gotoifisgtr(ARGUMENTS){
        std::variant<int, std::string> value1, value2;
        alphaTools::validateMark(arguments[2].getValue(), markers);

        if (arguments[0].getType() == alph_variable){
            Variable tmpvar = memory[arguments[0].getValue()];
            if (tmpvar.type == alph_string){
                value1 = tmpvar.str_value;
            }else{
                value1 = tmpvar.num_value;
            }
        }else if(arguments[0].getType() == alph_number){
            value1 = std::stoi(arguments[0].getValue());
        }else{//alph_string
            value1 = arguments[0].getValue();
        }

        if (arguments[1].getType() == alph_variable){
            Variable tmpvar = memory[arguments[1].getValue()];
            if (tmpvar.type == alph_string){
                value2 = tmpvar.str_value;
            }else{
                value2 = tmpvar.num_value;
            }
        }else if(arguments[1].getType() == alph_number){
            value2 = std::stoi(arguments[1].getValue());
        }else{//alph_string
            value2 = arguments[1].getValue();
        }

        if (value1 > value2){
            currLine = alphaTools::getTokenIndex(markers[arguments[2].getValue()], tokens);
        }
    }
}

void interpretCode(std::vector<Token> tokens, std::map<std::string, int> markers){
    //create a map to store what functions to call on what command
    std::map<std::string, Variable> memory;
    std::map<std::string, std::function<void(std::vector<Token>, std::map<std::string, Variable>&, int, int&, std::map<std::string, int>, std::vector<Token>)> > alph_commands;

    //std::cout << "got " << markers.size() << " markers, first one is at line " << alphaTools::getTokenIndex(markers["loop"], tokens) << "\n";

    alph_commands["print"] = alphCMDs::print;
    alph_commands["exit"] = alphCMDs::exit;
    alph_commands["let"] = alphCMDs::let;
    alph_commands["goto"] = alphCMDs::alph_goto;
    alph_commands["more"] = alphCMDs::more;
    alph_commands["less"] = alphCMDs::less;
    alph_commands["get"] = alphCMDs::get;
    alph_commands["debug"] = alphCMDs::debug;
    alph_commands["gotoifis"] = alphCMDs::gotoifis;
    alph_commands["gotoifisnt"] = alphCMDs::gotoifisnt;
    alph_commands["add"] = alphCMDs::add;
    alph_commands["sub"] = alphCMDs::sub;
    alph_commands["mul"] = alphCMDs::mul;
    alph_commands["div"] = alphCMDs::div;
    alph_commands["pow"] = alphCMDs::pow;
    alph_commands["mod"] = alphCMDs::mod;
    alph_commands["gotoifislss"] = alphCMDs::gotoifislss;
    alph_commands["gotoifisgtr"] = alphCMDs::gotoifisgtr;

    //main program loop
    int tokenIndex = 0;
    while(tokenIndex < tokens.size()){
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

        alph_commands[command.getValue()](arguments, memory, command.getLineNumber(), tokenIndex, markers, tokens);
    }
}
#endif