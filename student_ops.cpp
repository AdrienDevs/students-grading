#include "student_ops.h"
#include <algorithm>
#include <iterator>

void sortByName(Students& v) {
    std::sort(v.begin(), v.end(), [](const Person& a, const Person& b) {
        return a.name() != b.name() ? a.name() < b.name() : a.surname() < b.surname();
    });
}

void sortByFinal(Students& v) {
    std::sort(v.begin(), v.end(), [](const Person& a, const Person& b) {
        if (a.finalAverage() != b.finalAverage()) return a.finalAverage() < b.finalAverage();
        return a.name() != b.name() ? a.name() < b.name() : a.surname() < b.surname();
    });
}

SplitResult splitByGrade(Students& sorted, double threshold) {
    // Binary search for the first student who passed (works because the list is sorted by final).
    auto mid = std::partition_point(sorted.begin(), sorted.end(),
                                    [threshold](const Person& p) { return p.finalAverage() < threshold; });
    SplitResult r;
    r.failed.assign(std::make_move_iterator(sorted.begin()), std::make_move_iterator(mid));
    r.passed.assign(std::make_move_iterator(mid), std::make_move_iterator(sorted.end()));
    Students().swap(sorted);                        // release the (now empty) elements and their memory
    return r;
}