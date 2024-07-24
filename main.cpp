#include <parser.hpp>
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
        vector<ASTValue> values = vector<ASTValue>();

        values.push_back(ASTValue(0.4));
        values.push_back(ASTValue(4));
        values.push_back(ASTValue(true));
        values.push_back(ASTValue(ASTArray()));
        values.push_back(ASTValue(ASTObject()));
        std::cout << parse_util::parseValues(values) << endl;
    } else {
        cout << "ran tester" << endl;
    }
    exit(0);
}