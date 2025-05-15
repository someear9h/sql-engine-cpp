#include "lexer.h"
#include <iostream>


int main() {
    std::string input = "SELECT name FROM users WHERE age = 25;";
    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();

    for (const Token& token : tokens) {
        std::cout << "Token(";
        switch (token.type) {
            case TokenType::KEYWORD: std::cout << "KEYWORD"; break;
            case TokenType::IDENTIFIER: std::cout << "IDENTIFIER"; break;
            case TokenType::SYMBOL: std::cout << "SYMBOL"; break;
            case TokenType::NUMBER: std::cout << "NUMBER"; break;
            case TokenType::STRING: std::cout << "STRING"; break;
            case TokenType::END_OF_FILE: std::cout << "EOF"; break;
        }
        std::cout << ", \"" << token.value << "\")\n";
    }

    return 0;
}