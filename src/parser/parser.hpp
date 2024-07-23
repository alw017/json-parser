#pragma once
#include <lexer.hpp>
#include <token.hpp>

class Expr {
    public:
        const Expr* left;
        const Expr* right;
        const Token operation;

};


namespace parser {
    
        
}
