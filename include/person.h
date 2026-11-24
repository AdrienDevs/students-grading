#ifndef PERSON_H
#define PERSON_H

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

class Person {
public:
    Person();
    Person(const Person& other);                    // rule of three
    Person& operator=(const Person& other);         // rule of three
    ~Person();                                      // rule of three
    Person(Person&& other) noexcept;                // move operations (see Step 3)
    Person& operator=(Person&& other) noexcept;

    void setName(const std::string& n)    { name_ = n; }
    void setSurname(const std::string& s) { surname_ = s; }
    void setExam(int e)                   { exam_ = e; }
    void addHomework(int h)               { hw_.push_back(h); }
    void calcFinals();                              // call after all results are set

    const std::string& name()    const { return name_; }
    const std::string& surname() const { return surname_; }
    int  homework(std::size_t i) const { return hw_.at(i); }   // throws std::out_of_range
    std::size_t homeworkCount()  const { return hw_.size(); }
    double finalAverage() const { return finalAvg_; }
    double finalMedian()  const { return finalMed_; }

    // Parses "Name Surname hw1 hw2 ... exam". Throws std::invalid_argument / std::out_of_range.
    void parseLine(const std::string& line);

    friend std::istream& operator>>(std::istream& in, Person& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

private:
    std::string      name_, surname_;
    std::vector<int> hw_;
    int              exam_;
    double           finalAvg_, finalMed_;          // cached by calcFinals()
};

#endif