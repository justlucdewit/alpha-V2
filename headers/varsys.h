class Variable{
    public:
        const char* name;
        union{
            int num_value;
            std::string str_value;
        };
        Tokentype type;
};