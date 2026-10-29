# Students Grading

A C++ console application that calculates students' final grades from
homework and exam results. Data can be typed in, randomly generated, or
read from a file. The final grade can be based on the average or the median.

## Final grade formula

Final = 0.4 * HW + 0.6 * Exam

- HW = average (or median) of the homework results
- Exam = exam result



- To run the Release download the zip from the release, unzip it, and run:

   - g++ -std=c++17 -Wall -Wextra person.cpp main.cpp -o app
   - ./app
