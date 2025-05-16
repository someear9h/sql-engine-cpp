#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include "token.h"  // using shared Token definition

// AST Node for a basic SELECT statement like: SELECT name FROM users;
struct SelectStatement {
    std::vector<std::string> columns;
    std::string tableName;
};

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::shared_ptr<SelectStatement> parseSelect();

private:
    const std::vector<Token>& tokens;
    size_t position;

    const Token& peek() const;
    const Token& advance();
    bool match(TokenType type, const std::string& value = "");
};

#endif // PARSER_H
