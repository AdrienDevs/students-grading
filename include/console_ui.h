#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "students.h"

Students readManual();                                  // throws std::runtime_error on bad input
Students generateRandomConsole();
void printAvgOrMed(const Students& v, bool useMedian);
void printBoth(const Students& v);

#endif