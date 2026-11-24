cmake_minimum_required(VERSION 3.16)
project(StudentsGrading VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Speed tests are meaningless without optimization, so default to a Release build.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_executable(students
  src/main.cpp
  src/person.cpp
  src/student_io.cpp
  src/console_ui.cpp
  src/benchmark.cpp)

target_include_directories(students PRIVATE include)

if(MSVC)
  target_compile_options(students PRIVATE /W4)
else()
  target_compile_options(students PRIVATE -Wall -Wextra -pedantic)
endif()