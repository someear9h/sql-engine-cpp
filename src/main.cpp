#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"
#include <iostream>
#include <string>

int main() {
    std::string input = "SELECT name, age FROM students;";

    Lexer lexer(input);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    auto stmt = parser.parseSelect();

    Interpreter interpreter;
    interpreter.executeSelect(stmt);

    return 0;
}