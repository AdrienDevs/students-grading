#ifndef STUDENT_IO_H
#define STUDENT_IO_H

#include "students.h"
#include <cstddef>
#include <string>

// readStudents / writeStudents work with std::vector, std::list and std::deque
// (they are instantiated for these three in student_io.cpp).
// All functions throw std::runtime_error with a readable message on failure.
template <class Container>
Container readStudents(const std::string& path);

template <class Container>
void writeStudents(const std::string& path, const Container& v);

void generateStudentFile(const std::string& path, std::size_t count, std::size_t hwCount = 15);

#endif