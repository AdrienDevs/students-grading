#ifndef SPLIT_H
#define SPLIT_H

// Two strategies for dividing students into "failed" (< 5.0) and "passed" (>= 5.0),
// each written twice: as a plain hand-written loop and with <algorithm> functions.
// All functions are templates, so they work for std::vector, std::list and std::deque.

#include "students.h"
#include <algorithm>
#include <iterator>

constexpr double kPassMark = 5.0;

inline bool isFailed(const Person& p) { return p.finalAverage() < kPassMark; }
inline bool isPassed(const Person& p) { return !isFailed(p); }

// Give back unused memory after elements were erased (std::list has no such function).
template <class Container>
void shrinkToFit(Container& c) { c.shrink_to_fit(); }
inline void shrinkToFit(StudentsList&) {}

// ---------------------------------------------------------------------------
// STRATEGY 1: copy. 'all' keeps every student; 'failed' and 'passed' are new containers.
// ---------------------------------------------------------------------------
template <class Container>
void copySplitLoop(const Container& all, Container& failed, Container& passed) {
    for (const Person& p : all) {
        if (isFailed(p)) failed.push_back(p);
        else             passed.push_back(p);
    }
}

// remove_copy_if copies every element for which the predicate is FALSE.
template <class Container>
void copySplitAlgo(const Container& all, Container& failed, Container& passed) {
    std::remove_copy_if(all.begin(), all.end(), std::back_inserter(failed), isPassed);   // keeps the failed ones
    std::remove_copy_if(all.begin(), all.end(), std::back_inserter(passed), isFailed);   // keeps the passed ones
}

// ---------------------------------------------------------------------------
// STRATEGY 2: move. Failed students are moved to 'failed' and removed from 'all',
// so 'all' ends up holding only the passed students.
// ---------------------------------------------------------------------------

// Erase inside the loop. Cheap for std::list, but for vector/deque every erase shifts
// all the elements behind it: O(n^2) in total.
template <class Container>
void moveSplitLoop(Container& all, Container& failed) {
    for (auto it = all.begin(); it != all.end();) {
        if (isFailed(*it)) {
            failed.push_back(std::move(*it));
            it = all.erase(it);
        } else {
            ++it;
        }
    }
    shrinkToFit(all);
}

// partition: ONE pass puts the passed students first and the failed ones last,
// then the failed tail is moved out and erased in a single operation.
template <class Container>
void moveSplitPartition(Container& all, Container& failed) {
    auto mid = std::partition(all.begin(), all.end(), isPassed);
    failed.insert(failed.end(), std::make_move_iterator(mid), std::make_move_iterator(all.end()));
    all.erase(mid, all.end());
    shrinkToFit(all);
}

// Same, but stable_partition keeps the original order inside both groups.
template <class Container>
void moveSplitStable(Container& all, Container& failed) {
    auto mid = std::stable_partition(all.begin(), all.end(), isPassed);
    failed.insert(failed.end(), std::make_move_iterator(mid), std::make_move_iterator(all.end()));
    all.erase(mid, all.end());
    shrinkToFit(all);
}

#endif