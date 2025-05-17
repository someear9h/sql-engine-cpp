// Abstract Syntax Tree (SelectStatement)

#ifndef AST_H
#define AST_H

#pragma once
#include <vector>
#include <string>
#include <memory>

// Defines the structure of a SELECT query
struct SelectStatement {
    std::vector<std::string> columns;
    std::string tableName;
};

using ASTNode = std::shared_ptr<SelectStatement>;

#endif // AST_H
