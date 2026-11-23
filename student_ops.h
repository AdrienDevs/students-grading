#ifndef STUDENT_OPS_H
#define STUDENT_OPS_H

#include "students.h"

struct SplitResult {
    Students failed;    // final (average) < 5.0
    Students passed;    // final (average) >= 5.0
};

void sortByName(Students& v);                       // by name, then surname
void sortByFinal(Students& v);                      // ascending by final (average)
SplitResult splitByGrade(Students& sorted, double threshold = 5.0);   // input must be sorted by final

#endif