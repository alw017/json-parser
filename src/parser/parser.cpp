#include "parser.hpp"

template<typename ... Ts>                                                 
struct Overload : Ts ... { 
    using Ts::operator() ...;
};
template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

auto TypeOfASTValue = Overload {                                     
        [](double) { return "double"; },
        [](int) { return "int"; },
        [](ASTArray& arr) { return "Array"; },
        [](ASTObject& obj) { return "Object"; },
        [](bool) { return "bool"; },
        [](std::string) {return "string";},
        [](auto) { return "unknown type"; },
    };


std::string parse_util::parseValues(std::vector<ASTValue> values) {
    std::string output = "";
    for (auto v : values) {
        output += std::visit(TypeOfASTValue, v.value);
    }
    return output;
}

ASTObject Parser::parseTokens() {
    advance();
    return object();
}

bool Parser::atEnd() {
    return peek().type == ENDFILE;
}

bool Parser::match(std::vector<TokenType> types) {
    for(auto t : types) {
        if (check(t)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) {
    if(atEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!atEnd()) return tokens[current++];
    else return tokens[current];
}

Token Parser::peek() {
    return tokens[current];
}

ASTObject Parser::object() { //TODO Error Checking.
    std::vector<ASTMember> members = std::vector<ASTMember>();
    if (peek().type == RIGHT_BRACE) {
        return ASTObject();
    } else {
        members.push_back(member());
        while (check(COMMA)) {
            advance();
            members.push_back(member());
        }
        advance();
        return ASTObject(members);
    }
}

ASTMember Parser::member() {
    if (check(STRING)) {
        Token keyToken = advance();
        std::string key = std::get<std::string>(keyToken.literal);
        advance();
        return ASTMember(key, value());
    } else {
        error(peek().line, "Expected string, got " + peek().type);
    }
}

ASTArray Parser::array() {
    if (peek().type == RIGHT_BRACKET) {
        advance(); // consume right bracket.
        return ASTArray();
    } else {
        std::vector<ASTValue*> values = std::vector<ASTValue*>();
        values.push_back(value());
        while (check(COMMA)) {
            advance(); // consume comma
            values.push_back(value());
        }
        advance(); // consume right bracket.
        return ASTArray(values);
    }
}

ASTValue * Parser::value() {
    Token t = advance();
    switch (t.type) {
        case NUMBER:
            return new ASTValue(std::get<double>(t.literal));
        case STRING:
            return new ASTValue(std::get<std::string>(t.literal));
        case TRUE:
            return new ASTValue(true);
        case FALSE:
            return new ASTValue(false);
        case NULLVALUE:
            return new ASTValue(0);
        case LEFT_BRACE: // {}
            return new ASTValue(object());
        case LEFT_BRACKET: // []
            return new ASTValue(array());
        default:
            error(t.line, "Unexpected symbol " + t.lexeme);
            break;
    }
} 


void Parser::error(int line, std::string message) {
    report(line, "", message);
    // add error recovery here.
}

void Parser::report(int line, std::string where, std::string message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
}