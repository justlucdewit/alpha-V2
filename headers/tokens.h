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
    Tokentype type = alph_unkown;
    std::string value = "";

    std::string getTypeFromEnum(){
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
    Tokentype getType(){
        return type;
    }

    std::string getValue(){
        return value;
    }

    void setType(Tokentype t){
        type = t;
    }

    void setValue(std::string v){
        value = v;
    }

    void debug(){
        std::cout << "Token[type=" << getTypeFromEnum() << ", value=" << value << "]\n";
    }

    Token clone(){
        Token ret;
        ret.value = value;
        ret.type = type;
        return ret;
    }

    void reset(){
        value = "";
        type = alph_unkown;
    }
};

std::vector<Token> lexer(std::string code){
    std::vector<Token> tokens;
    Token currentToken;

    int readingString = 0;
    bool readingComment = false;

    for (int i = 0; i < code.length(); i++){
        char currentChar = code[i];

        if (readingString == 0 && !readingComment){
            if (currentChar == '\''){
                readingString = 1;
                continue;
            }else if (currentChar == '"'){
                readingString = 2;
                continue;
            }else if (currentChar == '#'){
                readingComment = true;
                continue;
            }

            if (currentChar == ' ' || currentChar == '\n'){
                if (currentToken.getValue() != ""){
                    //std::cout << currentToken.getValue() << "\n";
                    tokens.push_back(currentToken.clone());
                    currentToken.reset();
                }
            }else{
                currentToken.setValue(currentToken.getValue()+currentChar);
            }
        }else if (readingComment){
            if (currentChar == '\n'){
                readingComment = false;
            }
        }else if (readingString == 1){
            if (currentChar == '\''){
                readingString = 0;
            }else{
                currentToken.setValue(currentToken.getValue()+currentChar);
            }
        }else if (readingString == 2){
            if (currentChar == '\"'){
                readingString = 0;
            }else{
                currentToken.setValue(currentToken.getValue()+currentChar);
            }
        }
    }

    std::cout << currentToken.getValue() << "\n";

    return tokens;
}