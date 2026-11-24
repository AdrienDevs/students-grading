#ifndef STUDENT_OPS_H
#define STUDENT_OPS_H

#include "students.h"
#include <algorithm>

inline bool byName(const Person& a, const Person& b) {
    return a.name() != b.name() ? a.name() < b.name() : a.surname() < b.surname();
}

inline bool byFinal(const Person& a, const Person& b) {
    if (a.finalAverage() != b.finalAverage()) return a.finalAverage() < b.finalAverage();
    return byName(a, b);
}

// std::sort needs random-access iterators: fine for vector and deque ...
template <class Container>
void sortByName(Container& v)  { std::sort(v.begin(), v.end(), byName); }

template <class Container>
void sortByFinal(Container& v) { std::sort(v.begin(), v.end(), byFinal); }

// ... but std::list has no random access, so it uses its own member function sort().
inline void sortByName(StudentsList& v)  { v.sort(byName); }
inline void sortByFinal(StudentsList& v) { v.sort(byFinal); }

#endif