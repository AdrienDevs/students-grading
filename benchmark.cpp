#include "benchmark.h"
#include <cstdio>

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

void printBenchHeader() {
    std::printf("%-10s %-28s %10s %8s %8s %8s %8s %9s\n",
                "Container", "File", "Records", "Read", "Sort", "Split", "Write", "TOTAL (s)");
    std::printf("%s\n", std::string(100, '-').c_str());
}

void printBenchRow(const BenchResult& r) {
    std::printf("%-10s %-28s %10zu %8.3f %8.3f %8.3f %8.3f %9.3f\n",
                r.container.c_str(), r.file.c_str(), r.records, r.read, r.sort, r.split, r.write, r.total);
    std::fflush(stdout);
}