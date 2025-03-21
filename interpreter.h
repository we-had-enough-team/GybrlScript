#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <unordered_map>
#include <variant>
#include <functional>
#include <sstream>

class NeanderthalInterpreter {
public:
    void interpret(const std::string& code);

private:
    using VarType = std::variant<int, std::string>;
    std::unordered_map<std::string, VarType> int_variables;
    std::unordered_map<std::string, VarType> str_variables;

    std::unordered_map<std::string, std::function<void(std::istringstream&)>> commandHandlers;
};

#endif // INTERPRETER_H end