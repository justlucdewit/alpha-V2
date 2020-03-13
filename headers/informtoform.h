#include "tokens.h"

Tokentype informToForm(std::string informal){
    if (informal == "var"){
        return alph_variable;
    }else if (informal == "num"){
        return alph_number;
    }else if (informal == "str"){
        return alph_string;
    }else if (informal == "mark"){
        return alph_marker;
    }else{
        std::cout << "[ERROR] acconfig.json has commands with invalid types";
        std::exit(1);
    }
}