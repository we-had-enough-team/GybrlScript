#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <string>

extern bool SkipERRS;
extern bool ReduceWarnings;

void ShowException(const std::string& cmdn, const std::string& reason, int warnlvl, bool& skipWarnings);

#endif // ERROR_HANDLING_H end