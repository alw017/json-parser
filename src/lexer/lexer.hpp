#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <sstream>
#include "token.hpp"

class Lexer {
    public:
        Lexer(std::string text, std::vector<Token>& list);
        bool run();
    private:
        int start = 0;
        int current = 0;
        int line = 1;
        int length;
        bool hasError = false;
        std::string source;
        std::vector<Token>& tokens;

        bool atEnd();
        void scanToken();
        void error(int line, std::string message);
        void report(int line, std::string where, std::string message);
        char advance();
        void addToken(TokenType type);
        void addToken(TokenType type, std::string str);
        void addToken(TokenType type, int num);
        void addToken(TokenType type, double num);
        char peek();
        char peekNext();
        void string();
        void number();
        bool isDigit(char c);
        bool isAlpha(char c);
        bool isHex(char c);
        void keyword();
};
