#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "split.h"
#include "student_io.h"
#include "student_ops.h"
#include "timer.h"
#include <cstddef>
#include <string>
#include <type_traits>
#include <vector>

enum class Strategy { Copy = 1, Move = 2 };
enum class Method   { Loop = 1, Algorithm = 2, Stable = 3 };

// Strategy 2 with a hand-written erase loop is O(n^2) for vector and deque.
// Above this many records it is skipped (change the number to try it anyway).
constexpr std::size_t kEraseLoopLimit = 100000;

struct BenchResult {
    std::string container, method, file;
    Strategy strategy = Strategy::Copy;
    bool skipped = false;
    std::size_t records = 0, failed = 0, passed = 0;
    double read = 0, split = 0, sort = 0, write = 0, total = 0;     // seconds
};

const std::vector<std::size_t>& testSizes();                        // 1 000 ... 10 000 000
std::string testFileName(std::size_t count);                        // random_students_<count>.txt
std::string outputName(const std::string& path, const std::string& tag);
std::string methodName(Strategy s, Method m);

void printBenchHeader();
void printBenchRow(const BenchResult& r);

// read -> split (chosen strategy and method) -> sort both groups -> write two files
template <class Container>
BenchResult runPipeline(const std::string& path, const std::string& containerName,
                        Strategy strategy, Method method) {
    BenchResult r;
    r.container = containerName;
    r.strategy = strategy;
    r.method = methodName(strategy, method);
    r.file = path;
    Timer total, t;

    Container all = readStudents<Container>(path);
    r.read = t.elapsed();
    r.records = all.size();

    const bool quadratic = strategy == Strategy::Move && method == Method::Loop
                           && !std::is_same<Container, StudentsList>::value;
    if (quadratic && r.records > kEraseLoopLimit) {
        r.skipped = true;
        return r;
    }

    Container failed, passedCopy;
    Container* passed = &passedCopy;                // strategy 2: the passed students stay in 'all'

    t.reset();
    if (strategy == Strategy::Copy) {
        if (method == Method::Loop) copySplitLoop(all, failed, passedCopy);
        else                        copySplitAlgo(all, failed, passedCopy);
    } else {
        passed = &all;
        if (method == Method::Loop)           moveSplitLoop(all, failed);
        else if (method == Method::Algorithm) moveSplitPartition(all, failed);
        else                                  moveSplitStable(all, failed);
    }
    r.split = t.elapsed();
    r.failed = failed.size();
    r.passed = passed->size();

    t.reset();
    sortByFinal(failed);
    sortByFinal(*passed);
    r.sort = t.elapsed();

    t.reset();
    writeStudents(outputName(path, "failed"), failed);
    writeStudents(outputName(path, "passed"), *passed);
    r.write = t.elapsed();

    r.total = total.elapsed();
    return r;
}

// Runs the pipeline for the container chosen by number: 1 = vector, 2 = list, 3 = deque.
BenchResult runByContainerNumber(int container, const std::string& path, Strategy s, Method m);

// Every container x every strategy/method on one file.
void benchmarkEverything(const std::string& path);

#endif