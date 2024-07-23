#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include "lexer.hpp"

class ConfigFile {
    private:
        std::string file;
        Lexer * lexer;

    public:
        ConfigFile(char * filename);
        ~ConfigFile();
        
        void runFile(); // void for now but later it will return a map of relevant key/value pairs.
};
    

#endif