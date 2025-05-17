// logic to execute SELECT

#pragma once
#include "ast.h"
#include <vector>
#include <unordered_map>
#include <string>

class Interpreter {
public:
    void executeSelect(const std::shared_ptr<SelectStatement> &stmt) const;
        
private:
    using Table = std::vector<std::unordered_map<std::string, std::string>>;

    Table getTable(const std::string &name) const;
};