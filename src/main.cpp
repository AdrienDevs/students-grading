#include "benchmark.h"
#include "console_ui.h"
#include "student_io.h"
#include "student_ops.h"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

int askNumber(const std::string& question, int lo, int hi) {
    std::cout << question;
    int x;
    if (!(std::cin >> x) || x < lo || x > hi)
        throw std::invalid_argument("please enter a number from " + std::to_string(lo) + " to " + std::to_string(hi));
    return x;
}

std::string askFile() {
    std::string path;
    std::cout << "File name: ";
    std::cin >> path;
    return path;
}

void showFile() {
    Students s = readStudents<Students>(askFile());
    sortByName(s);
    printBoth(s);
}

void generateAllFiles() {
    for (std::size_t n : testSizes()) {
        std::cout << "Generating " << testFileName(n) << " ... " << std::flush;
        generateStudentFile(testFileName(n), n);
        std::cout << "done\n";
    }
}

void runOneCombination() {
    int container = askNumber("Container (1 - vector, 2 - list, 3 - deque): ", 1, 3);
    int strategy  = askNumber("Strategy (1 - copy to two new containers, 2 - move failed out of the base container): ", 1, 2);
    int method    = (strategy == 1)
        ? askNumber("Method (1 - loop, 2 - remove_copy_if): ", 1, 2)
        : askNumber("Method (1 - loop with erase, 2 - partition, 3 - stable_partition): ", 1, 3);
    std::string path = askFile();
    printBenchHeader();
    printBenchRow(runByContainerNumber(container, path, static_cast<Strategy>(strategy), static_cast<Method>(method)));
}

void benchmarkOneFile() {
    std::string path = askFile();
    printBenchHeader();
    benchmarkEverything(path);
}

void benchmarkAllFiles() {
    printBenchHeader();
    for (std::size_t n : testSizes()) {
        benchmarkEverything(testFileName(n));
        std::cout << '\n';
    }
}

} // namespace

int main() {
    while (true) {
        std::cout << "\n1 - enter data manually\n"
                     "2 - generate random data (console)\n"
                     "3 - read a file and show the table\n"
                     "4 - generate the five random student files\n"
                     "5 - run ONE combination (container, strategy, method)\n"
                     "6 - compare EVERYTHING on one file\n"
                     "7 - compare EVERYTHING on the five generated files\n"
                     "0 - exit\nChoice: ";
        int choice;
        if (!(std::cin >> choice)) return 0;            // end of input / not a number
        if (choice == 0) return 0;

        try {
            switch (choice) {
            case 1: case 2: {
                Students s = (choice == 1) ? readManual() : generateRandomConsole();
                std::cout << "Final grade by (a)verage or (m)edian? ";
                char c;
                std::cin >> c;
                sortByName(s);
                printAvgOrMed(s, c == 'm' || c == 'M');
                break;
            }
            case 3: showFile();           break;
            case 4: generateAllFiles();   break;
            case 5: runOneCombination();  break;
            case 6: benchmarkOneFile();   break;
            case 7: benchmarkAllFiles();  break;
            default: std::cout << "Unknown choice\n";
            }
        } catch (const std::exception& e) {             // one place that reports every error
            std::cerr << "Error: " << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}