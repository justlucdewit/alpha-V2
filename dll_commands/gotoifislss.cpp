#define ARGUMENTS std::vector<Token> arguments, std::map<std::string, Variable>& memory, int lineNr, int& currLine, std::map<std::string, int> markers, std::vector<Token> tokens

#include <iostream>
#include <variant>
#include <vector>
#include <map>

#include "../headers/alphaTools.h"
#include "../headers/tokens.h"
#include "../headers/varsys.h"

namespace alphCMDs{
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
            value1 = std::stold(arguments[0].getValue());
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
            value2 = std::stold(arguments[1].getValue());
        }else{//alph_string
            value2 = arguments[1].getValue();
        }

        if (value1 < value2){
            currLine = alphaTools::getTokenIndex(markers[arguments[2].getValue()], tokens);
        }
    }
}