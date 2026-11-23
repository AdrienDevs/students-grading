#ifndef STUDENT_OPS_H
#define STUDENT_OPS_H

#include "students.h"
#include <algorithm>
#include <iterator>

template <class Container>
struct SplitResult {
    Container failed;    // final (average) < 5.0
    Container passed;    // final (average) >= 5.0
};

inline bool byName(const Person& a, const Person& b) {
    return a.name() != b.name() ? a.name() < b.name() : a.surname() < b.surname();
}

inline bool byFinal(const Person& a, const Person& b) {
    if (a.finalAverage() != b.finalAverage()) return a.finalAverage() < b.finalAverage();
    return byName(a, b);
}

// ---- sorting -------------------------------------------------------------
// std::sort needs random-access iterators: fine for vector and deque ...
template <class Container>
void sortByName(Container& v)  { std::sort(v.begin(), v.end(), byName); }

template <class Container>
void sortByFinal(Container& v) { std::sort(v.begin(), v.end(), byFinal); }

// ... but std::list has no random access, so it uses its own member function sort().
inline void sortByName(StudentsList& v)  { v.sort(byName); }
inline void sortByFinal(StudentsList& v) { v.sort(byFinal); }

// ---- splitting (input must be sorted by final) ---------------------------
template <class Container>
SplitResult<Container> splitByGrade(Container& sorted, double threshold = 5.0) {
    auto mid = std::partition_point(sorted.begin(), sorted.end(),
                                    [threshold](const Person& p) { return p.finalAverage() < threshold; });
    SplitResult<Container> r;
    r.failed.assign(std::make_move_iterator(sorted.begin()), std::make_move_iterator(mid));
    r.passed.assign(std::make_move_iterator(mid), std::make_move_iterator(sorted.end()));
    Container().swap(sorted);                       // release the (now empty) elements and their memory
    return r;
}

// std::list can re-link its nodes: splice() moves them without copying or moving any Person.
inline SplitResult<StudentsList> splitByGrade(StudentsList& sorted, double threshold = 5.0) {
    auto mid = std::partition_point(sorted.begin(), sorted.end(),
                                    [threshold](const Person& p) { return p.finalAverage() < threshold; });
    SplitResult<StudentsList> r;
    r.failed.splice(r.failed.begin(), sorted, sorted.begin(), mid);
    r.passed.splice(r.passed.begin(), sorted);      // whatever is left
    return r;
}

#endif