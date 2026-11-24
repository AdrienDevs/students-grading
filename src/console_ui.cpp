#include "console_ui.h"
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

Students readManual() {
    Students v;
    char more = 'y';
    while (more == 'y' || more == 'Y') {
        Person p;
        std::cin >> p;
        if (!std::cin) throw std::runtime_error("Invalid input: a number was expected");
        v.push_back(std::move(p));
        std::cout << "Add another student? (y/n): ";
        std::cin >> more;
    }
    return v;
}

Students generateRandomConsole() {
    int count, hwCount;
    std::cout << "How many students? ";              std::cin >> count;
    std::cout << "How many homework results each? "; std::cin >> hwCount;
    if (!std::cin || count < 0 || hwCount < 0) throw std::runtime_error("Invalid number");

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> grade(1, 10);
    Students v;
    v.reserve(count);
    for (int i = 1; i <= count; ++i) {
        Person p;
        p.setName("Name" + std::to_string(i));
        p.setSurname("Surname" + std::to_string(i));
        for (int j = 0; j < hwCount; ++j) p.addHomework(grade(gen));
        p.setExam(grade(gen));
        p.calcFinals();
        v.push_back(std::move(p));
    }
    return v;
}

void printAvgOrMed(const Students& v, bool useMedian) {
    const char* title = useMedian ? "Final_Point(Med.)" : "Final_Point(Aver.)";
    std::cout << '\n' << std::left << std::setw(14) << "Name" << std::setw(16) << "Surname"
              << std::right << std::setw(18) << title << '\n'
              << std::string(48, '-') << '\n';
    for (const Person& p : v)
        std::cout << p << std::right << std::setw(18) << std::fixed << std::setprecision(2)
                  << (useMedian ? p.finalMedian() : p.finalAverage()) << '\n';
}

void printBoth(const Students& v) {
    std::cout << std::left << std::setw(14) << "Name" << std::setw(16) << "Surname"
              << std::right << std::setw(14) << "Final (Avg.)" << " | " << std::setw(12) << "Final (Med.)" << '\n'
              << std::string(14 + 16 + 14 + 3 + 12, '-') << '\n';
    for (const Person& p : v)
        std::cout << p << std::right << std::setw(14) << std::fixed << std::setprecision(2)
                  << p.finalAverage() << " | " << std::setw(12) << p.finalMedian() << '\n';
}