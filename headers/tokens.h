#include <iostream>
#include <string>
#include <vector>

enum Tokentype{
    alph_command,
    alph_string,
    alph_integer,
    alph_variable,
    alph_marker,
    alph_unkown
};

class Token{
private:
    Tokentype type;
    std::string value;

    std::string getType(){
        switch(type){
            case alph_command: return "command";
            case alph_string: return "string";
            case alph_integer: return "integer";
            case alph_variable: return "variable";
            case alph_marker: return "marker";
        }
        
        return "unkown";
    }

public:
    Tokentype getTypeEnum(){
        return type;
    }

    std::string getValue(){
        return value;
    }

    void set(Tokentype t, std::string v){
        type = t;
        value = v;
    }

    void debug(){
        std::cout << "token\n  type: " << getType() << "\n  value: " << value;
    }
};

std::vector<Token> lexer(std::string code){
    std::vector<Token> tokens;

    std::string currentTokenValue = "";
    Tokentype currentTokenType = alph_unkown;
    int currentValueLen = 0;
    for (int i = 0; i < code.length(); i++){
        char currentChar = code[i];
        //std::cout << currentChar;
        if (currentChar == ' '){
            if (currentTokenValue != ""){
                std::cout << currentTokenValue;
                currentTokenValue.assign("");
                currentValueLen = 0;
            }
        }else{
            currentTokenValue[currentValueLen] = currentChar;
            currentValueLen++;
        }
    }

    return tokens;
}