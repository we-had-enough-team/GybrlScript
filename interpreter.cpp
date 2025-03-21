#include "interpreter.h"
#include <iostream>
#include "error_handling.h"

void NeanderthalInterpreter::interpret(const std::string& code) {
    std::istringstream stream(code);
    std::string command;

    commandHandlers = {
        {"printline", [this](std::istringstream& stream) {
            std::string say;
            stream >> say;
            std::cout << say;
        }},
        {"reduce_error_catching", [](std::istringstream&) { ReduceWarnings = true; SkipERRS = true; }},
        {"reduce_warnings", [](std::istringstream&) { SkipERRS = true; }},
        {"newline", [](std::istringstream&) { std::cout << std::endl; }},
        {"sum", [this](std::istringstream& stream) {
            int num1, num2;
            stream >> num1 >> num2;
            std::cout << (num1 + num2) << std::endl;
        }},
        {"multiply", [this](std::istringstream& stream) {
            int num1, num2;
            stream >> num1 >> num2;
            std::cout << (num1 * num2) << std::endl;
        }},
        {"set", [this](std::istringstream& stream) {
            std::string varType, varName, value;
            stream >> varType >> varName >> value;
            if (varType == "int") {
                int_variables[varName] = std::stoi(value);
            } else if (varType == "str") {
                str_variables[varName] = value;
            }
        }},
        {"get", [this](std::istringstream& stream) {
            std::string varName;
            stream >> varName;
            if (int_variables.find(varName) != int_variables.end()) {
                std::cout << std::get<int>(int_variables[varName]) << std::endl;
            } else if (str_variables.find(varName) != str_variables.end()) {
                std::cout << std::get<std::string>(str_variables[varName]) << std::endl;
            } else {
                std::cout << "Var " << varName << " not found" << std::endl;
            }
        }},
        {"getline", [this](std::istringstream& stream) {
            std::string var_name, var_type;
            stream >> var_type >> var_name;
            if (var_type == "int") {
                int input;
                std::cin >> input;
                int_variables[var_name] = input;
            } else if (var_type == "str") {
                std::string input;
                std::cin >> input;
                str_variables[var_name] = input;
            }
        }},
        {"if", [this](std::istringstream& stream) {
            std::string varName1, varName2, condition;
            stream >> varName1 >> condition >> varName2;
            if (int_variables.find(varName1) != int_variables.end() && int_variables.find(varName2) != int_variables.end()) {
                int var1 = std::get<int>(int_variables[varName1]);
                int var2 = std::get<int>(int_variables[varName2]);
                if (condition == "==") {
                    std::cout << (var1 == var2 ? "True" : "False") << std::endl;
                } else if (condition == "!=") {
                    std::cout << (var1 != var2 ? "True" : "False") << std::endl;
                } else if (condition == "<") {
                    std::cout << (var1 < var2 ? "True" : "False") << std::endl;
                } else if (condition == ">") {
                    std::cout << (var1 > var2 ? "True" : "False") << std::endl;
                } else if (condition == "<=") {
                    std::cout << (var1 <= var2 ? "True" : "False") << std::endl;
                } else if (condition == ">=") {
                    std::cout << (var1 >= var2 ? "True" : "False") << std::endl;
                } else {
                    std::cout << "Invalid condition" << std::endl;
                }
            } else {
                ShowException("if statement", "Unexisting vars in int-var-container", 3, SkipERRS);
            }
        }}
    };

    while (stream >> command) {
        if (command == ">>") {
            std::string to_skip;
            std::getline(stream, to_skip);
            continue;
        }

        auto it = commandHandlers.find(command);
        if (it != commandHandlers.end()) {
            it->second(stream);
        } else {
            ShowException(command, "Unknown command", 1, SkipERRS);
        }
    }
}