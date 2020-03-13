/*
    alpha code is a project started by luc de wit
    it was started on 12-2-2020

    it was originally meant to be a improvement on
    the language zettacode made by joseph catanzarit
*/

#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "headers/interpreter.h"
#include "headers/createfiles.h"
#include "headers/getmarkers.h"
#include "headers/getconfig.h"
#include "headers/validator.h"
#include "headers/readfile.h"
#include "headers/tokens.h"
#include "headers/varsys.h"

#include "commands/gotoifislss.h"
#include "commands/gotoifisgtr.h"
#include "commands/gotoifisnt.h"
#include "commands/gotoifis.h"
#include "commands/debug.h"
#include "commands/print.h"
#include "commands/exit.h"
#include "commands/more.h"
#include "commands/goto.h"
#include "commands/less.h"
#include "commands/let.h"
#include "commands/get.h"
#include "commands/add.h"
#include "commands/sub.h"
#include "commands/mul.h"
#include "commands/div.h"
#include "commands/pow.h"
#include "commands/mod.h"

#define VERSION "alpha V2.2.3"

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main(int argc, char** argv){
    std::map<std::string, std::function<void(std::vector<Token>, std::map<std::string, Variable>&, int, int&, std::map<std::string, int>, std::vector<Token>, bool&)> > alph_commands;

    alph_commands["gotoifislss"] = alphCMDs::gotoifislss;
    alph_commands["gotoifisgtr"] = alphCMDs::gotoifisgtr;
    alph_commands["gotoifisnt"] = alphCMDs::gotoifisnt;
    alph_commands["gotoifis"] = alphCMDs::gotoifis;
    alph_commands["goto"] = alphCMDs::alph_goto;
    alph_commands["debug"] = alphCMDs::debug;
    alph_commands["print"] = alphCMDs::print;
    alph_commands["exit"] = alphCMDs::exit;
    alph_commands["more"] = alphCMDs::more;
    alph_commands["less"] = alphCMDs::less;
    alph_commands["add"] = alphCMDs::add;
    alph_commands["sub"] = alphCMDs::sub;
    alph_commands["mul"] = alphCMDs::mul;
    alph_commands["div"] = alphCMDs::div;
    alph_commands["pow"] = alphCMDs::pow;
    alph_commands["mod"] = alphCMDs::mod;
    alph_commands["let"] = alphCMDs::let;
    alph_commands["get"] = alphCMDs::get;

    std::map<std::string, std::vector<std::vector<Tokentype>>> argData;
    argData["debug"] = {};
    argData["more"] = {{alph_variable}};
    argData["less"] = {{alph_variable}};
    argData["goto"] = {{alph_variable}};
    argData["print"] = {{alph_string, alph_variable, alph_number}};
    argData["get"] = {{alph_variable}};
    argData["exit"] = {{alph_number, alph_variable}};
    argData["let"] = {{alph_variable}, {alph_string, alph_number}};
    argData["gotoifis"] = {{alph_variable, alph_number, alph_string},{alph_variable, alph_number, alph_string}, {alph_variable}};
    argData["gotoifisnt"] ={{alph_variable, alph_number, alph_string},{alph_variable, alph_number, alph_string}, {alph_variable}};
    argData["add"] = {{alph_variable}, {alph_variable, alph_number}};
    argData["sub"] = {{alph_variable}, {alph_variable, alph_number}};
    argData["mul"] = {{alph_variable}, {alph_variable, alph_number}};
    argData["div"] = {{alph_variable}, {alph_variable, alph_number}};
    argData["pow"] = {{alph_variable}, {alph_variable, alph_number}};
    argData["mod"] = {{alph_variable}, {alph_variable, alph_number}};
    argData["gotoifislss"] = {{alph_variable, alph_number, alph_string},{alph_variable, alph_number, alph_string}, {alph_variable}};
    argData["gotoifisgtr"] = {{alph_variable, alph_number, alph_string},{alph_variable, alph_number, alph_string}, {alph_variable}};

    bool timed = false;
    
    //extract argv flags
    for (int i = 0; i < argc; i++){
        if (argv[i][0] == '-'){
            if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--time") == 0 ){
                timed = true;
            }
        }
    }
    
    if (argc >= 2){
        if (strcmp(argv[1], "run") == 0){
            if (argc >= 3){
                uint64_t beginTime, lexTime, valTime, itpTime;
                //fetch acconfig
                getconfig(argv[2]);

                //lexing
                beginTime = timeSinceEpochMillisec();
                std::vector<Token> tokens = lexer(readFile(argv[2]), argData);
                std::map<std::string, int> markers = getMarkers(tokens);
                lexTime = timeSinceEpochMillisec() - beginTime;
                
                //validating
                beginTime = timeSinceEpochMillisec();
                validator(tokens, argData);
                valTime = timeSinceEpochMillisec() - beginTime;

                //interpreting
                beginTime = timeSinceEpochMillisec();
                interpretCode(tokens, markers, alph_commands);
                itpTime = timeSinceEpochMillisec() - beginTime;

                if(timed){
                    std::cout << "\n\n--------run stats--------\n";
                    std::cout << "lexing:\t\t" << lexTime << " ms\n";
                    std::cout << "validating:\t" << valTime << " ms\n";
                    std::cout << "interpreting:\t" << itpTime << " ms\n";
                    std::cout << "-------------------------";
                }
                
                return 1;
            }else{
                std::cout << "[ERROR] you need to specify what program to run, for example: alpha run example.ac";
                return 1;
            }
        }else if (strcmp(argv[1], "make") == 0){
            if (argc >= 4){
                char* name = argv[3];
                if (strcmp(argv[2], "command") == 0){
                    createFolder(name);
                }else if(strcmp(argv[2], "project") == 0){
                    createFolder(name);
                }
            }else{
                std::cout << "[ERROR] to little arguments given for alpha make, see alpha help";
            }
            return 1;
        }else if (strcmp(argv[1], "version") == 0){
            std::cout << VERSION;
            return 1;
        }else if (strcmp(argv[1], "help") == 0){
            std::cout << "alpha run [path/to/script.ac]\n";
            std::cout << "\truns a alphacode script\n";

            std::cout << "\nalpha make [type] [name]\n";
            std::cout << "creates a new project, wich can either be a type of command,\nor project";

            std::cout << "\nalpha version\n";
            std::cout << "\tdisplays the current version of alphacode\n";

            std::cout << "\nalpha help\n";
            std::cout << "\tdisplays a list of all currently available CLI commands\n";
            return 1;
        }else{
            std::cout << "[ERROR] command: " << argv[1] << " does not exist, try: alpha help";
            return 1;
        }
    }else{
        std::cout << "[ERROR] not command supplied, try: alpha help\n";
        return 1;
    }
    
    return 0;
}