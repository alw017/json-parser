#include "reader.hpp"
#include <parser.hpp>

using namespace std;

ConfigFile::ConfigFile(char * filename) {
    string filename_str = string(filename);
    ifstream conf_file(filename_str);
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
    //cout << file << endl;
    cout << "Lexer output:" << endl;
    string mystring = "test_string";
    std::vector<Token> tokens = vector<Token>();
    Lexer lexer = Lexer(file, tokens);
    if (!lexer.run()) {
        std::cerr << "Error occurred. Terminating program." << endl;
        exit(1);
    }
    for (Token token : tokens) {
      //cout << token.lexeme << "";
    }
    Parser parser = Parser(tokens);
    ASTMapObject * obj = parser.parseTokens();
    std::cout << "complete" << std::endl;

    std::cout << parse_util::string(obj) << endl;

    delete obj;
}