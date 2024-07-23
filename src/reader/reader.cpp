#include "reader.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <lexer.hpp>


using namespace std;

ConfigFile::ConfigFile(char * filename) {
    string filename_str = string(filename);
    ifstream conf_file(filename_str);
    lexer = new Lexer();
    if (!conf_file.is_open()) {
        cerr << "ERROR: File " << filename_str << " failed to open." << endl;
        exit(1);
    } else {
        ostringstream stream;
        stream << conf_file.rdbuf();
        file = stream.str();
    }
}

ConfigFile::~ConfigFile() {}

void ConfigFile::runFile() {
    cout << file << endl;
    cout << "Lexer output:" << endl;
    lexer->run("test");
}