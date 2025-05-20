// Abstract Syntax Tree (SelectStatement)

#ifndef AST_H
#define AST_H

#pragma once
#include <vector>
#include <string>
#include <memory>

enum class StatementType {
    SELECT,
    INSERT,
    DELETE
};

struct Expression {
    std::string column;
    std::string op;
    std::string value;
};

// Defines the structure of a SELECT query
struct SelectStatement {
    std::vector<std::string> columns;
    std::string tableName;
    std::shared_ptr<Expression> whereClause = nullptr;
};

struct InsertStatement {
    std::string tableName;
    std::vector<std::string> columns;
    std::vector<std::string> values;
};

struct DeleteStatement {
    std::string tableName;
    std::shared_ptr<Expression> whereClause = nullptr;
};

using ASTNode = std::shared_ptr<SelectStatement>;

#endif // AST_H
