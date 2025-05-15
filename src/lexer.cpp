#include "lexer.h"
// #warning "Compiling lexer.cpp"
#include <cctype>
#include <unordered_set>
#include <iostream>

Lexer::Lexer(const std::string& input) : input(input), position(0) {}

char Lexer::peek() const {
    return position < input.length() ? input[position] : '\0';
}

char Lexer::advance() {
    return position < input.length() ? input[position++] : '\0';
}

void Lexer::skipWhitespace() {
    while (std::isspace(peek())) advance();
}

Token Lexer::makeIdentifier() {
    std:: string value;
    while(std::isalnum(peek()) || peek() == '_') {
        value += advance();
    }

    static std::unordered_set<std::string> keywords = {
        "SELECT", "FROM", "WHERE", "INSERT", "INTO", "VALUES", "DELETE", "UPDATE", "SET"
    };

    if(keywords.count(value)) {
        return { TokenType::KEYWORD, value };;
    }

    return {TokenType::IDENTIFIER, value};
}

Token Lexer::makeNumber() {
    std::string value;
    while(std::isdigit(peek())) {
        value += advance();
    }

    return {TokenType::NUMBER, value};
}

Token Lexer::makeString() {
    advance(); // skip opening single quote '
    std::string value;
    while(peek() != '\'' && peek() != '\0') {
        value += advance();
    }

    advance();  // skip closing '
    return {TokenType::STRING, value};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens; // vector to store tokens
    while(peek() != '\0') {
        skipWhitespace(); // skip spaces or tabs
        char current = peek();

        if(std::isalpha(current)){ // check the character is letter?

            tokens.push_back(makeIdentifier());
        } else if(std::isdigit(current)) {
            tokens.push_back(makeNumber());
        } else if(current == '\'') {
            tokens.push_back(makeString());
        } else if (std::ispunct(current)) {
            std::string sym(1, advance());
            tokens.push_back({ TokenType::SYMBOL, sym });
        } else {
            advance(); // skip unknown characters
        }
    }

    tokens.push_back({ TokenType::END_OF_FILE, "" });
    return tokens;
}