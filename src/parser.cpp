#include "../include/parser.h"
#include "../include/token.h"

Parser::Parser(const std::vector<Token> &tokens): tokens(tokens), position(0) {}

const Token &Parser::peek() const {
    if(position < tokens.size()) {
        return tokens[position];
    }
    static Token eof = {TokenType::END_OF_FILE, ""};
    return eof;
}

const Token &Parser::advance() {
    if(position < tokens.size()) position++;
    return peek();
}

bool Parser::match(TokenType token, const std::string &value) {
    if(peek().type == token && (value.empty() || peek().value == value)) {
        advance();
        return true;
    }
    return false;
}

std::shared_ptr<SelectStatement> Parser::parseSelect() {
    auto stmt = std::make_shared<SelectStatement>();

    if(!match(TokenType::KEYWORD, "SELECT")) {
        throw std::runtime_error("Expected SELECT keyword");
    }

    // Parse column names (e.g., SELECT name, age FROM ...)
    while(true) {
        if(peek().type != TokenType::IDENTIFIER) {
            throw std::runtime_error("Expected column name");
        }

        stmt->columns.push_back(peek().value);
        advance();

        if(!match(TokenType::SYMBOL, ",")) {
            break;
        }
    }

    if(!match(TokenType::KEYWORD, "FROM")) {
        throw std::runtime_error("Expected FROM keyword");
    }


    if(peek().type != TokenType::IDENTIFIER) {
        throw std::runtime_error("Expected table name");
    }

    stmt->tableName = peek().value;
    advance();

    return stmt;
}