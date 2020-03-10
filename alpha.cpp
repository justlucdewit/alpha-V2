/*
    alpha code is a project started by luc de wit
    it was started on 12-2-2020

    it was originally meant to be a improvement on
    the language zettacode made by joseph catanzarit
*/

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "headers/interpreter.h"
#include "headers/getmarkers.h"
#include "headers/validator.h"
#include "headers/readfile.h"
#include "headers/tokens.h"

#define VERSION "alpha V2.2.0"

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main(int argc, char** argv){
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

                beginTime = timeSinceEpochMillisec();
                std::vector<Token> tokens = lexer(readFile(argv[2]));
                std::map<std::string, int> markers = getMarkers(tokens);
                lexTime = timeSinceEpochMillisec() - beginTime;
                
                beginTime = timeSinceEpochMillisec();
                validator(tokens);
                valTime = timeSinceEpochMillisec() - beginTime;

                beginTime = timeSinceEpochMillisec();
                interpretCode(tokens, markers);
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
        }else if (strcmp(argv[1], "version") == 0){
            std::cout << VERSION;
            return 1;
        }else if (strcmp(argv[1], "help") == 0){
            std::cout << "alpha run [path/to/script.ac]\n";
            std::cout << "\truns a alphacode script\n";

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