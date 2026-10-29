#ifndef PERSON_H
#define PERSON_H

#include <cstddef>
#include <iostream>
#include <string>

class Person {
public:
    Person();
    Person(const Person& other);                // rule of three
    Person& operator=(const Person& other);     // rule of three
    ~Person();                                  // rule of three

    void calcFinalAverage();

    friend std::istream& operator>>(std::istream& in, Person& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

private:
    std::string name_, surname_;
    int*        hw_;
    std::size_t n_;
    int         exam_;
    double      final_;
};

#endif