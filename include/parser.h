#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include "token.h"  // using shared Token definition
#include "ast.h"

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
