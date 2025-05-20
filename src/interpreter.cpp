#include "../include/interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

using Row = std::unordered_map<std::string, std::string>;
using Table = std::vector<Row>;

Table Interpreter::loadTable(const std::string &tableName) const {
    std::string path = "tables/" + tableName + ".csv";
    std::ifstream file(path);
    Table table;

    if (!file.is_open()) {
        throw std::runtime_error("Table file not found: " + path);
    }

    std::string line;
    std::vector<std::string> headers;

    // read header
    if(getline(file, line)) {
        std::istringstream ss(line);
        std::string col;

        while(getline(ss, col, ',')) {
            headers.push_back(col);
        }
    }

    // read rows
    while(getline(file, line)) {
        std::istringstream ss(line);
        std::string cell;
        Row row;
        size_t idx = 0;

        while (getline(ss, cell, ',') && idx < headers.size()) {
            row[headers[idx++]] = cell;
        }

        table.push_back(row);
    }
    return table;
}

void Interpreter::saveTable(const std::string &tableName, const Table &table) const {
    if(table.empty()) return;

    std::string path = "tables/" + tableName + ".csv";
    std::ofstream file(path);

    const auto &headers = table[0];
    // Write headers
    for(auto it = headers.begin(); it != headers.end(); ++it) {
        if(it != headers.begin()) file << ",";
        file << it->first;
    }
    file << "\n";

    // Write rows
    for(const auto &row : table) {
        for(auto it = row.begin(); it != row.end(); ++it) {
            if(it != row.begin()) file << ",";
            file << it->second;
        }
        file << "\n";
    }
}

bool Interpreter::rowMatchesWhere(const Row &row, const std::shared_ptr<Expression> &where) const {
    if(!where) return true;

    auto it = row.find(where->column);
    if(it == row.end()) return false;

    // Currently only supports "=" condition
    if(where->op == "=") {
        return it->second == where->value;
    }

    return false;
}

void Interpreter::executeSelect(const std::shared_ptr<SelectStatement> &stmt) const {
    Table table = loadTable(stmt->tableName);

    if (table.empty()) {
        std::cout << "No data.\n";
        return;
    }

    // Determine columns
    std::vector<std::string> columns;
    if (stmt->columns.size() == 1 && stmt->columns[0] == "*") {
        for (const auto &col : table[0]) {
            columns.push_back(col.first);
        }
    } else {
        columns = stmt->columns;
    }

    // Print header
    for (const auto &col : columns) {
        std::cout << col << "\t";
    }
    std::cout << "\n";

    // Print matching rows
    for (const auto &row : table) {
        if (!rowMatchesWhere(row, stmt->whereClause)) continue;

        for (const auto &col : columns) {
            auto it = row.find(col);
            if (it != row.end()) {
                std::cout << it->second << "\t";
            } else {
                std::cout << "NULL\t";
            }
        }
        std::cout << "\n";
    }
}

void Interpreter::executeInsert(const std::shared_ptr<InsertStatement> &stmt) {
    Table table = loadTable(stmt->tableName);

    Row newRow;
    for (size_t i = 0; i < stmt->columns.size(); ++i) {
        newRow[stmt->columns[i]] = stmt->values[i];
    }

    table.push_back(newRow);
    saveTable(stmt->tableName, table);

    std::cout << "Inserted 1 row.\n";
}

void Interpreter::executeDelete(const std::shared_ptr<DeleteStatement> &stmt) {
    Table table = loadTable(stmt->tableName);

    Table filtered;
    for (const auto &row : table) {
        if (!rowMatchesWhere(row, stmt->whereClause)) {
            filtered.push_back(row);
        }
    }

    saveTable(stmt->tableName, filtered);
    std::cout << "Deleted rows.\n";
}
