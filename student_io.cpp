#include "student_io.h"
#include <cstdio>
#include <fstream>
#include <random>
#include <stdexcept>

Students readStudents(const std::string& path) {
    std::ifstream f(path);
    if (!f) throw std::runtime_error("Cannot open file: " + path);

    Students v;
    std::string line;
    if (!std::getline(f, line)) throw std::runtime_error("File is empty: " + path);   // header line

    std::size_t lineNo = 1;
    while (std::getline(f, line)) {
        ++lineNo;
        if (line.find_first_not_of(" \t\r") == std::string::npos) continue;           // blank line
        Person p;
        try {
            p.parseLine(line);
        } catch (const std::exception& e) {
            throw std::runtime_error(path + ":" + std::to_string(lineNo) + ": " + e.what());
        }
        v.push_back(std::move(p));
    }
    return v;
}

void writeStudents(const std::string& path, const Students& v) {
    std::ofstream out(path);
    if (!out) throw std::runtime_error("Cannot create file: " + path);

    std::string buf;
    buf.reserve(1 << 20);
    buf += "Name          Surname           Final (Avg.) | Final (Med.)\n";
    buf += std::string(59, '-') + '\n';
    char line[160];
    for (const Person& p : v) {
        std::snprintf(line, sizeof line, "%-14s%-16s%14.2f | %12.2f\n",
                      p.name().c_str(), p.surname().c_str(), p.finalAverage(), p.finalMedian());
        buf += line;
        if (buf.size() > (1 << 20) - 200) { out << buf; buf.clear(); }                // flush in 1 MB chunks
    }
    out << buf;
    if (!out) throw std::runtime_error("Write error: " + path);
}

void generateStudentFile(const std::string& path, std::size_t count, std::size_t hwCount) {
    std::ofstream out(path);
    if (!out) throw std::runtime_error("Cannot create file: " + path);

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> grade(1, 10);

    std::string buf = "Name Surname";
    for (std::size_t j = 1; j <= hwCount; ++j) buf += " HW" + std::to_string(j);
    buf += " Exam\n";

    for (std::size_t i = 1; i <= count; ++i) {
        buf += "Name" + std::to_string(i) + " Surname" + std::to_string(i);
        for (std::size_t j = 0; j <= hwCount; ++j) {                                  // hwCount homework + 1 exam
            int g = grade(gen);
            buf += ' ';
            if (g == 10) buf += "10"; else buf += static_cast<char>('0' + g);
        }
        buf += '\n';
        if (buf.size() > (1 << 20)) { out << buf; buf.clear(); }
    }
    out << buf;
    if (!out) throw std::runtime_error("Write error: " + path);
}