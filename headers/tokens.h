#include <iostream>
#include <string>
#include <vector>

enum Tokentype{
    alph_command,
    alph_string,
    alph_number,
    alph_variable,
    alph_marker,
    alph_unkown
};

bool isCommand(const std::string str){
    if (str=="goto"||str=="let"||str=="more"||str=="less"||str=="print"||str=="get"||str=="exit"||str=="debug"){
        return true;
    }
    return false;
}

bool isNumber(std::string str){
    for (int i = 0; i < str.length(); i++){
        switch(str[i]){
            case '0':continue;
            case '1':continue;
            case '2':continue;
            case '3':continue;
            case '4':continue;
            case '5':continue;
            case '6':continue;
            case '7':continue;
            case '8':continue;
            case '9':continue;
            default:return false;
        }
    }
    return true;
}

class Token{
private:
    Tokentype type = alph_unkown;
    std::string value = "";

    std::string getTypeFromEnum(){
        switch(type){
            case alph_command: return "command";
            case alph_string: return "string";
            case alph_number: return "number";
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
                currentToken.setType(alph_string);
                readingString = 1;
                continue;
            }else if (currentChar == '"'){
                currentToken.setType(alph_string);
                readingString = 2;
                continue;
            }else if (currentChar == '#'){
                readingComment = true;
                continue;
            }

            if (currentChar == ' ' || currentChar == '\n'){
                if (currentToken.getValue() != ""){
                    if (currentToken.getType() == alph_unkown){
                        if (isCommand(currentToken.getValue())){
                            currentToken.setType(alph_command);
                        }else if(currentToken.getValue()[0] == ':'){
                            currentToken.setType(alph_marker);
                            currentToken.setValue(currentToken.getValue().erase(0, 1));
                        }else if(isNumber(currentToken.getValue())){
                            currentToken.setType(alph_number);
                        }else{
                            currentToken.setType(alph_variable);
                        }
                    }
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

    if (currentToken.getValue() != ""){
        tokens.push_back(currentToken);
    }

    return tokens;
}