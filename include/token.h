#ifndef TOKEN_H
#define TOKEN_H

#include <string>

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

#endif // TOKEN_H
