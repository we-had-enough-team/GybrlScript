#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>

bool SkipERRS = false;

void ShowException(std::string cmdn, std::string reason, int warnlvl, bool& skipWarnings) {
    switch (warnlvl) {
        case 1: {
            if (skipWarnings) {
                return;
            }

            std::string choise_run = "N";
            std::cout << std::endl
                      << "The '" << cmdn << "' command caused a non-critical error in the program."
                      << std::endl << "Reason: " << reason << std::endl
                      << "Continue program execution? [N(no)|Y(yes)|A(always)] #>> ";
            std::cin >> choise_run;

            if (choise_run == "A") {
                skipWarnings = true;
                return;
            } else if (choise_run != "Y") {
                choise_run = "N";
            }

            if (choise_run == "N") {
                std::cerr << "Program terminated due to error." << std::endl;
                exit(EXIT_FAILURE);
            }
            break;
        }
        case 2: {
            std::string choise_run = "N";
            std::cout << std::endl
                      << "The '" << cmdn << "' command caused a senior error in the program."
                      << std::endl << "Reason: " << reason << std::endl
                      << "It is strongly recommended not to continue program execution." << std::endl
                      << "Continue program execution? [N(no)|Y(yes)] #>> ";
            std::cin >> choise_run;

            if (choise_run != "Y") {
                choise_run = "N";
            }

            if (choise_run == "N") {
                std::cerr << "Program terminated due to error." << std::endl;
                exit(EXIT_FAILURE);
            }
            break;
        }
        case 3: {
            std::cout << std::endl
                      << "Critical error occurred with the '" << cmdn << "' command."
                      << std::endl << "Reason: " << reason << std::endl
                      << "The program may behave unpredictably. Exiting now." << std::endl;
            exit(EXIT_FAILURE);
            break;
        }
        default:
            std::cout << "Unknown warning level: " << warnlvl << std::endl;
            break;
    }
}


class NeanderthalInterpreter {
public:
    void interpret(const std::string& code) {
        std::istringstream stream(code);
        std::string command;

        while (stream >> command) {
            if (command == ">>") {
                std::string to_skip;
                std::getline(stream, to_skip);
                continue;
            }
            if (command == "printline") {
                std::string say;
                stream >> say;
                std::cout << say;
            } else if (command == "newline") {
                std::cout << std::endl;
            } else if (command == "sum") {
                int num1, num2;
                stream >> num1 >> num2;
                std::cout << (num1 + num2) << std::endl;
            } else if (command == "multiply") {
                int num1, num2;
                stream >> num1 >> num2;
                std::cout << (num1 * num2) << std::endl;
            } else if (command == "set") {
                std::string varType, varName;
                std::string value;
                stream >> varType >> varName >> value;
                if (varType == "int") {
                    int_variables[varName] = std::stoi(value);
                } else if (varType == "str") {
                    str_variables[varName] = value;
                }
            } else if (command == "get") {
                std::string varName;
                stream >> varName;
                if (int_variables.find(varName) != int_variables.end()) {
                    std::cout << std::get<int>(int_variables[varName]) << std::endl;
                } else if (str_variables.find(varName) != str_variables.end()) {
                    std::cout << std::get<std::string>(str_variables[varName]) << std::endl;
                } else {
                    std::cout << "Var " << varName << " not found" << std::endl;
                }
            } else if (command == "getline") {
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
            } else if (command == "if") {
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
                    ShowException("if statement", "Unexisting vars in int-var-container", 2, SkipERRS);
                }
            } else {
                ShowException(command, "Unknown command", 1, SkipERRS);
            }
        }
    }

private:
    using VarType = std::variant<int, std::string>;
    std::unordered_map<std::string, VarType> int_variables;
    std::unordered_map<std::string, VarType> str_variables;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file name>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        ShowException("File Loader", argv[1], 3, SkipERRS);;
        std::cerr << "Exception while loading file: " << argv[1] << std::endl;
        return 1;
    }

    std::string code;
    std::string line;
    while (std::getline(file, line)) {
        code += line + "\n";
    }

    NeanderthalInterpreter interpreter;
    interpreter.interpret(code);

    return 0;
}