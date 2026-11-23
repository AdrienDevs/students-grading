#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <cstddef>
#include <string>
#include <vector>

struct BenchResult {
    std::string file;
    std::size_t records = 0, failed = 0, passed = 0;
    double read = 0, sort = 0, split = 0, write = 0, total = 0;     // seconds
};

const std::vector<std::size_t>& testSizes();                        // 1 000 ... 10 000 000
std::string testFileName(std::size_t count);                        // random_students_<count>.txt

BenchResult runPipeline(const std::string& path);                   // read -> sort -> split -> write 2 files
void printBenchHeader();
void printBenchRow(const BenchResult& r);

#endif