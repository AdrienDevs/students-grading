#include "benchmark.h"
#include "student_io.h"
#include "student_ops.h"
#include "timer.h"
#include <cstdio>

const std::vector<std::size_t>& testSizes() {
    static const std::vector<std::size_t> sizes = {1000, 10000, 100000, 1000000, 10000000};
    return sizes;
}

std::string testFileName(std::size_t count) {
    return "random_students_" + std::to_string(count) + ".txt";
}

// "data/students.txt" + "failed" -> "data/students_failed.txt"
static std::string outputName(const std::string& path, const std::string& tag) {
    std::size_t dot = path.find_last_of('.');
    std::size_t slash = path.find_last_of("/\\");
    if (dot == std::string::npos || (slash != std::string::npos && dot < slash))
        return path + "_" + tag + ".txt";
    return path.substr(0, dot) + "_" + tag + path.substr(dot);
}

BenchResult runPipeline(const std::string& path) {
    BenchResult r;
    r.file = path;
    Timer total, t;

    Students all = readStudents(path);
    r.read = t.elapsed();
    r.records = all.size();

    t.reset();
    sortByFinal(all);
    r.sort = t.elapsed();

    t.reset();
    SplitResult parts = splitByGrade(all);
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

void printBenchHeader() {
    std::printf("%-30s %10s %8s %8s %8s %8s %9s\n",
                "File", "Records", "Read", "Sort", "Split", "Write", "TOTAL (s)");
    std::printf("%s\n", std::string(95, '-').c_str());
}

void printBenchRow(const BenchResult& r) {
    std::printf("%-30s %10zu %8.3f %8.3f %8.3f %8.3f %9.3f   (failed %zu / passed %zu)\n",
                r.file.c_str(), r.records, r.read, r.sort, r.split, r.write, r.total, r.failed, r.passed);
    std::fflush(stdout);
}