#include "lexer.hpp"

Lexer::Lexer(std::string text, std::vector<Token>& list) : length(text.length()), source(text), tokens(list) {}

std::string Token::str() {
    return std::to_string(type) + " " + lexeme;
}

bool Lexer::atEnd() {
    return current >= length;
}

char Lexer::advance() {
    return source[current++];
}

void Lexer::addToken(TokenType type) {
    std::string text = source.substr(start, current-start);
    tokens.push_back(Token(type, text, "", line));
}

void Lexer::addToken(TokenType type, std::string literal) {
    std::string text = source.substr(start, current-start);
    tokens.push_back(Token(type, text, literal, line));
}

void Lexer::addToken(TokenType type, int literal) {
    std::string text = source.substr(start, current-start);
    tokens.push_back(Token(type, text, literal, line));
}

void Lexer::addToken(TokenType type, double literal) {
    std::string text = source.substr(start, current-start);
    tokens.push_back(Token(type, text, literal, line));
}

char Lexer::peek() {
    if (atEnd()) return '\0';
    return source[current];
}

void Lexer::string() {
    std::stringstream ss{""};
    while (peek() != '"' && !atEnd()) {
        //std::cout << peek() << " ";
        if (peek() == '\\') {
            switch (peekNext()) {
                case '"': 
                    ss << '\"'; advance(); advance(); break;
                case '\\':
                    ss << '\\'; advance(); advance(); break;
                case '/':
                    ss << '/'; advance(); advance(); break;
                case 'b':
                    ss << '\b'; advance(); advance(); break;
                case 'f':
                    ss << '\f'; advance(); advance(); break;
                case 'n':
                    ss << '\n'; advance(); advance(); break;
                case 't':
                    ss << '\t'; advance(); advance(); break;
                case 'r':
                    ss << '\r'; advance(); advance(); break;
                case 'u': // 
                    advance(); 
                    advance();
                    for(int i = 0; i < 4; i++) {
                        if (isHex(peek())) {
                            advance();
                        } else {
                            error(line, "invalid hex escape");
                            break;
                        }
                    }
                    error(line, "utf-16 characters will be ignored");
                    break;
                default:
                    std::string s(1, peek());
                    std::string s1(1, peekNext());
                    advance(); // consume the erroneous escape.
                    error(line, "bad escape on " + s + s1);
                    break;
            }
        } else {
            ss << advance();
        };
    }

    //std::cout << "resulting string: " << ss.str() << std::endl;

    if (atEnd()) {
        error(line, "Unterminated string");
        return;
    }

    advance(); // consume right quote
    //std::string value = source.substr(start + 1, current - 2 - start);
    addToken(STRING, ss.str());
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::isHex(char c) {
    return isDigit(c) || 
        (c >= 'a' && c <= 'f') ||
        (c >= 'A' && c <= 'F'); 
}

void Lexer::number() {
    bool isDouble = false;
    while(isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext())) {
        advance();
        while (isDigit(peek())) advance();
        isDouble = true;
    }
    if ((peek() == 'e' || peek() == 'E') && (isDigit(peekNext()) || peekNext() == '+' || peekNext() == '-')) {
        advance(); // take e/E and +/- or digit.
        advance();
        while(isDigit(peek())) advance();
        isDouble = true;
    }
    if (true/*isDouble*/) {
            addToken(NUMBER, std::strtod(source.substr(start,current-start).c_str(), nullptr));
    } else {
            addToken(NUMBER, std::stoi(source.substr(start, current-start)));
    }
} 

char Lexer::peekNext() {
    if (current + 1 >= length) return '\0';
    return source[current + 1];
}

void Lexer::scanToken() {
    char c = advance();
    switch(c) {
        case '{': addToken(LEFT_BRACE); break;
        case '}': addToken(RIGHT_BRACE); break;
        case '[': addToken(LEFT_BRACKET); break;
        case ']': addToken(RIGHT_BRACKET); break;
        case ',': addToken(COMMA); break;
        case ':': addToken(COLON); break;
        case ' ':
        case '\r':
        case '\t': break;
        case '\n': line++; break; // newline
        case '"': string(); break;
        case '-': number(); break;
        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                keyword();
            } else {
                std::string s(1, c);
                error(line, "Unexpected character: " + s + " " + std::to_string(c));
            }
            break;
    }
}

void Lexer::keyword() {
    while (isAlpha(peek())) advance() ;
    std::string text = source.substr(start, current - start);
    if (text == "true") {
        addToken(TRUE);
    } else if (text == "false") {
        addToken(FALSE);
    } else if (text == "null") {
        addToken(NULLVALUE);
    } else {
        error(line, "Unexpected identifier: " + text + ", expected true, false, or null");
    }
            
}

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');
}

bool Lexer::run() {
    while(!atEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back(Token(ENDFILE, "EOF", "", line));
    return true;
}

void Lexer::error(int line, std::string message) {
    report(line, "", message);
}

void Lexer::report(int line, std::string where, std::string message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
}