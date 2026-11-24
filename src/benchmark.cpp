#include "benchmark.h"
#include <cstdio>
#include <stdexcept>

const std::vector<std::size_t>& testSizes() {
    static const std::vector<std::size_t> sizes = {1000, 10000, 100000, 1000000, 10000000};
    return sizes;
}

std::string testFileName(std::size_t count) {
    return "random_students_" + std::to_string(count) + ".txt";
}

// "data/students.txt" + "failed" -> "data/students_failed.txt"
std::string outputName(const std::string& path, const std::string& tag) {
    std::size_t dot = path.find_last_of('.');
    std::size_t slash = path.find_last_of("/\\");
    if (dot == std::string::npos || (slash != std::string::npos && dot < slash))
        return path + "_" + tag + ".txt";
    return path.substr(0, dot) + "_" + tag + path.substr(dot);
}

std::string methodName(Strategy s, Method m) {
    if (m == Method::Loop) return "loop";
    if (m == Method::Stable) return "stable_partition";
    return s == Strategy::Copy ? "remove_copy_if" : "partition";
}

BenchResult runByContainerNumber(int container, const std::string& path, Strategy s, Method m) {
    switch (container) {
    case 1: return runPipeline<StudentsVector>(path, "vector", s, m);
    case 2: return runPipeline<StudentsList>(path, "list", s, m);
    case 3: return runPipeline<StudentsDeque>(path, "deque", s, m);
    default: throw std::invalid_argument("container must be 1 (vector), 2 (list) or 3 (deque)");
    }
}

void benchmarkEverything(const std::string& path) {
    struct Combo { Strategy s; Method m; };
    const Combo combos[] = {
        {Strategy::Copy, Method::Loop},      {Strategy::Copy, Method::Algorithm},
        {Strategy::Move, Method::Loop},      {Strategy::Move, Method::Algorithm},
        {Strategy::Move, Method::Stable}};
    for (int c = 1; c <= 3; ++c)
        for (const Combo& k : combos)
            printBenchRow(runByContainerNumber(c, path, k.s, k.m));
}

void printBenchHeader() {
    std::printf("%-8s %-3s %-17s %-26s %9s %8s %8s %8s %8s %9s\n",
                "Cont.", "Str", "Method", "File", "Records", "Read", "Split", "Sort", "Write", "TOTAL (s)");
    std::printf("%s\n", std::string(112, '-').c_str());
}

void printBenchRow(const BenchResult& r) {
    if (r.skipped) {
        std::printf("%-8s %-3d %-17s %-26s %9zu   skipped: erase loop is O(n^2) above %zu records\n",
                    r.container.c_str(), static_cast<int>(r.strategy), r.method.c_str(),
                    r.file.c_str(), r.records, kEraseLoopLimit);
    } else {
        std::printf("%-8s %-3d %-17s %-26s %9zu %8.3f %8.3f %8.3f %8.3f %9.3f\n",
                    r.container.c_str(), static_cast<int>(r.strategy), r.method.c_str(),
                    r.file.c_str(), r.records, r.read, r.split, r.sort, r.write, r.total);
    }
    std::fflush(stdout);
}