#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "student_io.h"
#include "student_ops.h"
#include "timer.h"
#include <cstddef>
#include <string>
#include <vector>

struct BenchResult {
    std::string container, file;
    std::size_t records = 0, failed = 0, passed = 0;
    double read = 0, sort = 0, split = 0, write = 0, total = 0;     // seconds
};

const std::vector<std::size_t>& testSizes();                        // 1 000 ... 10 000 000
std::string testFileName(std::size_t count);                        // random_students_<count>.txt
std::string outputName(const std::string& path, const std::string& tag);   // x.txt + failed -> x_failed.txt

void printBenchHeader();
void printBenchRow(const BenchResult& r);

// read -> sort -> split -> write 2 files, for any of the three containers
template <class Container>
BenchResult runPipeline(const std::string& path, const std::string& containerName) {
    BenchResult r;
    r.container = containerName;
    r.file = path;
    Timer total, t;

    Container all = readStudents<Container>(path);
    r.read = t.elapsed();
    r.records = all.size();

    t.reset();
    sortByFinal(all);
    r.sort = t.elapsed();

    t.reset();
    SplitResult<Container> parts = splitByGrade(all);
    r.split = t.elapsed();
    r.failed = parts.failed.size();
    r.passed = parts.passed.size();

    t.reset();
    writeStudents(outputName(path, "failed"), parts.failed);
    writeStudents(outputName(path, "passed"), parts.passed);
    r.write = t.elapsed();

    r.total = total.elapsed();
    return r;
}

#endif