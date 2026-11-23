#ifndef STUDENTS_H
#define STUDENTS_H

#include "person.h"
#include <deque>
#include <list>
#include <vector>

// The three containers compared in this release.
using StudentsVector = std::vector<Person>;
using StudentsList   = std::list<Person>;
using StudentsDeque  = std::deque<Person>;

// Container used by the console menu (manual input, random data, show file).
using Students = StudentsVector;

#endif