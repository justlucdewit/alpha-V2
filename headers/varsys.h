#include <string>

#include "tokens.h"

struct Variable{
    const char* name;
    Tokentype type;

    int num_value;
    std::string str_value;
};