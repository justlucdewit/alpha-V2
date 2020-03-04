std::map<std::string, int> getMarkers(std::vector<Token>& tokens){
    std::map<std::string, int> markers;

    for (int i = 0; i <= tokens.size(); i++){
        if (tokens[i].getType() == alph_marker){
            markers[tokens[i].getValue()] = tokens[i].getLineNumber();
            tokens.erase(tokens.begin()+i);
        }
    }

    return markers;
}