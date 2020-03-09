#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable>& memory, int lineNr, int& currLine, std::map<std::string, int> markers, std::vector<Token> tokens

#include <iostream>
#include <vector>
#include <map>

#include "../headers/tokens.h"
#include "../headers/varsys.h"

namespace alphCMDs{
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
}