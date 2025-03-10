#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

/*
Абырвалгвывыв [текст который надо вывести]
Гыгыварлб [число которое надо вывести]
СЛОЖИ [число 1] [число 2]
УМНОЖЬ [число 1] [число 2]
ПРИСВИ [название переменной] [значение]
ПОЛУЧИ [название переменной]
*/

class NeanderthalInterpreter {
public:
    void interpret(const std::string& code) {
        std::istringstream stream(code);
        std::string command;

        while (stream >> command) {
            if (command == "Абырвалгвывыв") {
                std::string say;
                stream >> say;
                std::cout << say << std::endl;
            } else if (command == "Гыгыварлб") {
                int number;
                stream >> number;
                std::cout << number << std::endl;
            } else if (command == "СЛОЖИ") {
                int num1, num2;
                stream >> num1 >> num2;
                std::cout << (num1 + num2) << std::endl;
            } else if (command == "УМНОЖЬ") {
                int num1, num2;
                stream >> num1 >> num2;
                std::cout << (num1 * num2) << std::endl;
            } else if (command == "ПРИСВИ") {
                std::string varName;
                int value;
                stream >> varName >> value;
                variables[varName] = value;
            } else if (command == "ПОЛУЧИ") {
                std::string varName;
                stream >> varName;
                if (variables.find(varName) != variables.end()) {
                    std::cout << variables[varName] << std::endl;
                } else {
                    std::cout << "Переменная не найдена: " << varName << std::endl;
                }
            } else if (command == "слухай_суда_бл") {
                std::cin;
            } else {
                std::cout << "Неизвестная команда: " << command << std::endl;
            }
        }
    }

private:
    std::unordered_map<std::string, int> variables;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <имя_файла>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << argv[1] << std::endl;
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
