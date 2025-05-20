// logic to execute SELECT and other statements

#pragma once

#include "ast.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

class Interpreter {
public:
    void executeSelect(const std::shared_ptr<SelectStatement> &stmt) const;
    void executeInsert(const std::shared_ptr<InsertStatement> &stmt);
    void executeDelete(const std::shared_ptr<DeleteStatement> &stmt);
        
private:
    using Row = std::unordered_map<std::string, std::string>;
    using Table = std::vector<Row>;
    

    Table loadTable(const std::string &tableName) const;
    bool rowMatchesWhere(const Row &row, const std::shared_ptr<Expression> &where) const;
    void saveTable(const std::string &tableName, const Table &table) const;
};