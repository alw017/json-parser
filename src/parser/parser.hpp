#pragma once
#include <lexer.hpp>
#include <token.hpp>
#include <unordered_map>
#include <memory>

enum ASTNodeType {
    AST_STRING, AST_NULL, AST_FALSE, AST_TRUE, AST_NUMBER, AST_OBJECT, AST_ARRAY, AST_MEMBER, AST_VALUE
};

struct ASTValue;

struct ASTArray {
    std::vector<ASTValue*> arr;
    ASTArray() : arr(std::vector<ASTValue*>()) {}
    ASTArray(std::vector<ASTValue*> arr) : arr(arr) {}
};

struct ASTMember {
    std::string key;
    ASTValue* value;
    ASTMember(std::string key, ASTValue* value) : key(key), value(value) {} 
};

struct ASTObject {
    std::vector<ASTMember> members;
    ASTObject() : members(std::vector<ASTMember>()) {}
    ASTObject(std::vector<ASTMember> members) : members(members) {}
};

struct ASTValue {
    std::variant<int, double, bool, ASTObject, ASTArray, std::string> value;
    ASTValue(int val) : value(val) {}
    ASTValue(double val) : value(val) {}
    ASTValue(bool val) : value(val) {}
    ASTValue(ASTObject val) : value(val) {}
    ASTValue(ASTArray val) : value(val) {}
    ASTValue(std::string val) : value(val) {}
};

namespace parse_util {
    std::string parseValues(std::vector<ASTValue> values);
}

class Parser {
    private:
        int start = 0;
        int current = 0;
        int line;
        int length;
        const std::vector<Token> tokens;
        ASTObject object();
        ASTMember member();
        ASTArray array();
        double number();
        bool boolean();
        int nullvalue();
        std::string string();
        ASTValue * value();
    public: 
        ASTObject parseTokens();
        bool atEnd();
        bool scanExpr();
        void error(int line, std::string message);
        void report(int line, std::string where, std::string message);
        bool match(std::vector<TokenType> types);
        bool check(TokenType type);
        Token advance();
        Token peek();
        Token previous();
        Parser(std::vector<Token> tokens) : tokens(tokens), length(tokens.size()) {}
};

