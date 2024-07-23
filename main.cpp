#include <iostream>
#include <fstream>
#include <string>

#include <lexer.hpp>
#include <parser.hpp>
#include <reader.hpp>

using namespace std;

int main(int argc, char * argv[]) { 
    // placeholder testing behavior:

    if (argc > 2) {
        cerr << "Expected: tester <scriptName>" << endl;
        exit(1);
    } else if (argc == 2){
        ConfigFile conf_file(argv[1]);
        conf_file.runFile();
    } else {
        cout << "ran tester" << endl;
    }
    exit(0);
}