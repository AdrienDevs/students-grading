# Students Grading

A C++ console application that calculates students' final grades from homework
and exam results. Data can be typed in, randomly generated, or read from a file.
The final grade is based on the average or the median.

## Final grade formula

Final = 0.4 * HW + 0.6 * Exam

- HW = average (or median) of the homework results
- Exam = exam result

## Releases

### v0.1
`Person` class with the rule of three, final grade by average or median,
`std::vector`, random data, reading students from a file.

### v0.2
Refactoring into several `.h`/`.cpp` files, exception handling, generation of five
random student files (1 000 ... 10 000 000 records), splitting students into
"failed" (< 5.0) and "passed" (>= 5.0) files, speed analysis with `std::vector`.

### v0.25
The same program with `std::list` and `std::deque`; speed comparison of all
three containers.

### v1.0
Two strategies for splitting students, compared for all three containers, and a
refactoring with `<algorithm>` (`remove_copy_if`, `partition`, `stable_partition`).
Makefile and CMakeLists.txt added, clean repository structure.

## Usage guide

### Requirements
A C++17 compiler (g++ 8 or newer, clang, or MSVC) and `make` (Unix) or CMake 3.16+ (any OS).

### 1. Get the code
```bash
git clone https://github.com/<your-user>/students-grading.git
cd students-grading
```

### 2. Build with make (Unix)
```bash
make          # builds the program "students" (objects go to build/)
make run      # builds and starts it
make clean    # removes build/ and the program
```

### 2b. Build with CMake (any OS)
```bash
cmake -S . -B build
cmake --build build --config Release
```
Run `./build/students` (Windows: `build\Release\students.exe`).

### 3. Use the program
Start it and choose from the menu:

| Option | What it does |
|--------|--------------|
| 1 | Enter students by hand (homework ends with 0) |
| 2 | Generate random students in the console |
| 3 | Read a file and show the table (average and median) |
| 4 | Generate five random files (1 000 ... 10 000 000 records) |
| 5 | Run ONE combination: container, strategy, method, file |
| 6 | Compare everything on one file |
| 7 | Compare everything on the five generated files |
| 0 | Exit |

Typical first run: option 4 (generate files), then option 6 with
`random_students_100000.txt`. Results are written to `<file>_failed.txt`
and `<file>_passed.txt`.

### Input file format
The first line is a header and is skipped. Each other line is
`Name Surname hw1 hw2 ... exam`: the last number is the exam, the others are
homework results (0-10).

## Strategies

- **Strategy 1 (copy):** students are copied into two new containers, "failed" and "passed";
  the original container keeps everyone.
- **Strategy 2 (move):** failed students are moved to a new container and removed from the
  original, which keeps only the passed students.

Each strategy is implemented as a plain loop and with `<algorithm>`
(`std::remove_copy_if`; `std::partition` / `std::stable_partition`).

## Results

Computer: <CPU>, <RAM> GB, <SSD/HDD>, <OS>. Compiler: g++ <version>, `-std=c++17 -O2`.
Times in seconds.

### v0.2 and v0.25: containers
<table from your v0.2 and v0.25 runs>

### v1.0: strategies and methods
<table: container, strategy, method, split time, total, for 100 000 and 1 000 000 records>

### Memory
<peak memory, strategy 1 vs strategy 2>

### Comments
<what you observed: which container is fastest for splitting and for the whole program,
why erase in a vector/deque loop is slow, how much partition improved the split step,
how much memory strategy 2 saves, which algorithms were not faster>

## Project structure

| Path | Purpose |
|------|---------|
| `src/` | source files (`.cpp`) |
| `include/` | header files (`.h`) |
| `Makefile` | build with make (Unix) |
| `CMakeLists.txt` | build with CMake (any OS) |