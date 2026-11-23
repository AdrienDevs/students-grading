#ifndef STUDENT_IO_H
#define STUDENT_IO_H

#include "students.h"
#include <cstddef>
#include <string>

// All three throw std::runtime_error with a readable message on failure.
Students readStudents(const std::string& path);
void     writeStudents(const std::string& path, const Students& v);
void     generateStudentFile(const std::string& path, std::size_t count, std::size_t hwCount = 15);

#endif