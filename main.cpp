#include "person.h"
#include <iomanip>
#include <iostream>
#include <string>

int main() {
    int count;
    std::cout << "How many students? ";
    std::cin >> count;

    Person* students = new Person[count];
    for (int i = 0; i < count; ++i) {
        std::cin >> students[i];
        students[i].calcFinalAverage();
    }

    std::cout << '\n' << std::left << std::setw(12) << "Name" << std::setw(15) << "Surname"
              << std::right << std::setw(18) << "Final_Point(Aver.)" << '\n'
              << std::string(45, '-') << '\n';
    for (int i = 0; i < count; ++i) std::cout << students[i] << '\n';

    delete[] students;
    return 0;
}