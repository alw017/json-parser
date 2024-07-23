//#include <parser.hpp>
#include <reader.hpp>
#include <lexer.hpp>

using namespace std;

int main(int argc, char * argv[]) { 
    // placeholder testing behavior:

    if (argc > 2) {
        cerr << "Expected: tester <scriptName>" << endl;
        exit(1);
    } else if (argc == 2){
        //lexer::run_lexer("test");
        ConfigFile conf_file(argv[1]);
        conf_file.runFile();
    } else {
        cout << "ran tester" << endl;
    }
    exit(0);
}