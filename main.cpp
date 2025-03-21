#include <iostream>
#include <fstream>
#include "interpreter.h"
#include "error_handling.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file name>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        ShowException("File Loader", argv[1], 3, SkipERRS);
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