# Students Grading

A C++ console application that calculates students' final grades from
homework and exam results. Data can be typed in, randomly generated, or
read from a file. The final grade can be based on the average or the median.

## Final grade formula

Final = 0.4 * HW + 0.6 * Exam

- HW = average (or median) of the homework results
- Exam = exam result

## Releases

| Release | Description |
|---------|-------------|
| v0.1    | Person class (rule of three), average/median, std::vector, random data, file input |
| v0.2    | Refactoring into classes and header files, exception handling, random file generation, splitting students into "failed" and "passed", speed analysis (std::vector) |

## What's new in v0.2

- Code split into several `.h` / `.cpp` files (`Person`, file input/output, sorting and splitting, console menu, benchmark, `Timer`).
- Exception handling: a missing file, a malformed line, a grade outside 0-10 or invalid console input produce a clear error message instead of a crash.
- Generation of five random student files (1 000, 10 000, 100 000, 1 000 000 and 10 000 000 records).
- Students are sorted by final grade (average) and split into two files:
  - `*_failed.txt`: final grade < 5.0
  - `*_passed.txt`: final grade >= 5.0
- Speed measurement of each stage: reading, sorting, splitting, writing.

## Project structure

| File | Purpose |
|------|---------|
| `person.h/.cpp` | `Person` class (rule of three, move operations, parsing, final grades) |
| `students.h` | Container type used by the program (`std::vector<Person>`) |
| `student_io.h/.cpp` | Reading, writing and generating student files |
| `student_ops.h/.cpp` | Sorting and splitting students |
| `console_ui.h/.cpp` | Manual input, random console data, table output |
| `benchmark.h/.cpp` | Speed analysis of the whole pipeline |
| `timer.h` | `Timer` class (stopwatch) |
| `main.cpp` | Menu |

## How to build and run

Download the zip from the release, unzip it, and run:

```bash
g++ -std=c++17 -O2 -Wall -Wextra *.cpp -o app
./app
```

`-O2` (optimization) is important for the speed tests.

Menu options:

1. Enter data manually
2. Generate random data (console)
3. Read a file and show the table
4. Generate the five random student files
5. Speed test on the five generated files
6. Speed test on one file

### Input file format

The first line is a header and is skipped. Every other line is
`Name Surname hw1 hw2 ... exam`: the last number is the exam, the numbers before it
are homework results (0-10).

```
Name Surname HW1 HW2 HW3 Exam
Name1 Surname1 3 7 4 8
```

Note: the generated data files are not stored in this repository (they are
too large). Use menu option 4 to create them.

## Speed analysis (v0.2, std::vector)

Test computer: <CPU>, <RAM> GB RAM, <SSD/HDD>, <operating system>.
Compiler: g++ <version>, flags `-std=c++17 -O2`.
Times are in seconds.

| Records | Read | Sort | Split | Write | Total |
|---------|------|------|-------|-------|-------|
| 1 000 | | | | | |
| 10 000 | | | | | |
| 100 000 | | | | | |
| 1 000 000 | | | | | |
| 10 000 000 | | | | | |

### Conclusions

<2-4 sentences about what you observed.>



| v0.25   | The same program with std::list and std::deque containers, speed comparison of vector, list and deque |