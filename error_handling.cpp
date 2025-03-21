#include "error_handling.h"
#include <iostream>
#include <cstdlib>

bool SkipERRS = false;
bool ReduceWarnings = false;

void handleWarningLevel1(const std::string& cmdn, const std::string& reason, bool& skipWarnings) {
    if (skipWarnings) return;

    std::string choice;
    std::cout << "\nThe '" << cmdn << "' command caused a non-critical error.\nReason: " << reason
              << "\nContinue? [N(no)|Y(yes)|A(always)] #>> ";
    std::cin >> choice;

    if (choice == "A") {
        skipWarnings = true;
    } else if (choice != "Y") {
        std::cerr << "Program terminated due to error.\n";
        exit(EXIT_FAILURE);
    }
}

void handleWarningLevel2(const std::string& cmdn, const std::string& reason) {
    std::string choice;
    std::cout << "\nThe '" << cmdn << "' command caused a senior error.\nReason: " << reason
              << "\nIt is strongly recommended not to continue. Continue? [N(no)|Y(yes)] #>> ";
    std::cin >> choice;

    if (choice != "Y") {
        std::cerr << "Program terminated due to error.\n";
        exit(EXIT_FAILURE);
    }
}

void handleWarningLevel3(const std::string& cmdn, const std::string& reason) {
    std::cerr << "\nCritical error occurred with the '" << cmdn << "' command.\nReason: " << reason
              << "\nExiting now.\n";
    exit(EXIT_FAILURE);
}

void ShowException(const std::string& cmdn, const std::string& reason, int warnlvl, bool& skipWarnings) {
    if (ReduceWarnings) {
        std::cout << "Skipped: " << cmdn << std::endl;
        return;
    }

    switch (warnlvl) {
        case 1: handleWarningLevel1(cmdn, reason, skipWarnings); break;
        case 2: handleWarningLevel2(cmdn, reason); break;
        case 3: handleWarningLevel3(cmdn, reason); break;
        default:
            std::cerr << "Unknown warning level: " << warnlvl << std::endl;
            exit(EXIT_FAILURE);
    }
}