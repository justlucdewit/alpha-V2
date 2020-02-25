#include "tokens.h"

struct Variable{
    const char* name;
    Tokentype type;

    int num_value;
    const char* str_value;
    
    Variable() = default;
};