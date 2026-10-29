#include "person.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

void printAvgOrMed(const std::vector<Person>& v, bool useMedian) {
    const char* title = useMedian ? "Final_Point(Med.)" : "Final_Point(Aver.)";
    std::cout << '\n' << std::left << std::setw(14) << "Name" << std::setw(16) << "Surname"
              << std::right << std::setw(18) << title << '\n'
              << std::string(48, '-') << '\n';
    for (const Person& p : v)
        std::cout << p << std::right << std::setw(18) << std::fixed << std::setprecision(2)
                  << (useMedian ? p.finalMedian() : p.finalAverage()) << '\n';
}

void printBoth(const std::vector<Person>& v) {
    std::cout << std::left << std::setw(14) << "Name" << std::setw(16) << "Surname"
              << std::right << std::setw(14) << "Final (Avg.)" << " | " << std::setw(12) << "Final (Med.)" << '\n'
              << std::string(14 + 16 + 14 + 3 + 12, '-') << '\n';
    for (const Person& p : v)
        std::cout << p << std::right << std::setw(14) << std::fixed << std::setprecision(2)
                  << p.finalAverage() << " | " << std::setw(12) << p.finalMedian() << '\n';
}

void sortByName(std::vector<Person>& v) {
    std::sort(v.begin(), v.end(), [](const Person& a, const Person& b) {
        return a.name() != b.name() ? a.name() < b.name() : a.surname() < b.surname();
    });
}

std::vector<Person> readManual() {
    std::vector<Person> v;
    char more = 'y';
    while (more == 'y' || more == 'Y') {
        Person p;
        std::cin >> p;
        v.push_back(p);
        std::cout << "Add another student? (y/n): ";
        std::cin >> more;
    }
    return v;
}

std::vector<Person> generateRandom() {
    int count, hwCount;
    std::cout << "How many students? ";              std::cin >> count;
    std::cout << "How many homework results each? "; std::cin >> hwCount;
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> grade(1, 10);
    std::vector<Person> v;
    v.reserve(count);
    for (int i = 1; i <= count; ++i) {
        Person p;
        p.setName("Name" + std::to_string(i));
        p.setSurname("Surname" + std::to_string(i));
        for (int j = 0; j < hwCount; ++j) p.addHomework(grade(gen));
        p.setExam(grade(gen));
        v.push_back(p);
    }
    return v;
}

std::vector<Person> readFile(const std::string& path) {
    std::ifstream f(path);
    if (!f) throw std::runtime_error("Cannot open file: " + path);
    std::vector<Person> v;
    std::string line;
    std::getline(f, line);                      // skip the header line
    while (std::getline(f, line)) {
        Person p;
        if (p.parseLine(line)) v.push_back(std::move(p));
    }
    return v;
}

} // namespace

int main() {
    try {
        std::cout << "1 - enter data manually\n2 - generate random data\n3 - read from file\nChoice: ";
        int mode;
        std::cin >> mode;

        std::vector<Person> students;
        if (mode == 3) {
            std::string path;
            std::cout << "File name: "; std::cin >> path;
            students = readFile(path);
            sortByName(students);
            printBoth(students);
        } else {
            students = (mode == 1) ? readManual() : generateRandom();
            std::cout << "Final grade by (a)verage or (m)edian? ";
            char c; std::cin >> c;
            sortByName(students);
            printAvgOrMed(students, c == 'm' || c == 'M');
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}