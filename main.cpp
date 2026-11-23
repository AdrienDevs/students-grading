#include "benchmark.h"
#include "console_ui.h"
#include "student_io.h"
#include "student_ops.h"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

void showFile() {
    std::string path;
    std::cout << "File name: ";
    std::cin >> path;
    Students s = readStudents<Students>(path);
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

// The same file, the same steps, three different containers.
void benchmarkFile(const std::string& path) {
    printBenchRow(runPipeline<StudentsVector>(path, "vector"));
    printBenchRow(runPipeline<StudentsList>(path, "list"));
    printBenchRow(runPipeline<StudentsDeque>(path, "deque"));
}

void benchmarkAll() {
    printBenchHeader();
    for (std::size_t n : testSizes()) benchmarkFile(testFileName(n));
}

void benchmarkOne() {
    std::string path;
    std::cout << "File name: ";
    std::cin >> path;
    printBenchHeader();
    benchmarkFile(path);
}

} // namespace

int main() {
    while (true) {
        std::cout << "\n1 - enter data manually\n"
                     "2 - generate random data (console)\n"
                     "3 - read a file and show the table\n"
                     "4 - generate the five random student files\n"
                     "5 - speed test (vector, list, deque) on the five generated files\n"
                     "6 - speed test (vector, list, deque) on one file\n"
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
            case 3: showFile();         break;
            case 4: generateAllFiles(); break;
            case 5: benchmarkAll();     break;
            case 6: benchmarkOne();     break;
            default: std::cout << "Unknown choice\n";
            }
        } catch (const std::exception& e) {             // one place that reports every error
            std::cerr << "Error: " << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}