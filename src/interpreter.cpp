#include "../include/interpreter.h"
#include <iostream>

Interpreter::Table Interpreter::getTable(const std::string &name) const {
    if(name == "students") {
        return {
            {{"name", "Alice"}, {"age", "20"}, {"major", "CS"}},
            {{"name", "Bob"}, {"age", "22"}, {"major", "Math"}},
            {{"name", "Charlie"}, {"age", "21"}, {"major", "Physics"}}
        };
    }

    throw std::runtime_error("Table not found: " + name);
}

void Interpreter::executeSelect(const std::shared_ptr<SelectStatement> &stmt) const {
    Table table = getTable(stmt->tableName);

    // print header
    for(const auto& col : stmt->columns) {
        std::cout << col << "\t";
    }
    std::cout << "\n";

    // print rows
    for(const auto& row : table) {
        for(const auto& col : stmt->columns) {
            auto it = row.find(col);
            if(it != row.end()) {
                std::cout << it->second << "\t";
            } else {
                std::cout << "NULL\t";
            }
        }
        std::cout << "\n";
    }
}