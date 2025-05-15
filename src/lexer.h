#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    SYMBOL,
    NUMBER,
    STRING,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    char peek() const;
    char advance();
    void skipWhitespace();
    Token makeIdentifier();
    Token makeNumber();
    Token makeString();

    std::string input;
    size_t position;
};


#endif // LEXER_H