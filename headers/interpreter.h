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

#include "../commands/gotoifislss.h"
#include "../commands/gotoifisgtr.h"
#include "../commands/gotoifisnt.h"
#include "../commands/gotoifis.h"
#include "../commands/debug.h"
#include "../commands/print.h"
#include "../commands/exit.h"
#include "../commands/more.h"
#include "../commands/goto.h"
#include "../commands/less.h"
#include "../commands/let.h"
#include "../commands/get.h"
#include "../commands/add.h"
#include "../commands/sub.h"
#include "../commands/mul.h"
#include "../commands/div.h"
#include "../commands/pow.h"
#include "../commands/mod.h"

void interpretCode(std::vector<Token> tokens, std::map<std::string, int> markers){
    bool exiting = false;

    //create a map to store what functions to call on what command
    std::map<std::string, Variable> memory;
    std::map<std::string, std::function<void(std::vector<Token>, std::map<std::string, Variable>&, int, int&, std::map<std::string, int>, std::vector<Token>, bool&)> > alph_commands;

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