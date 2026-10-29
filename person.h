#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>

class Person {
public:
    Person();
    Person(const Person& other);                // rule of three
    Person& operator=(const Person& other);     // rule of three
    ~Person();                                  // rule of three

    void setName(const std::string& n)    { name_ = n; }
    void setSurname(const std::string& s) { surname_ = s; }
    void setExam(int e)                   { exam_ = e; }
    void addHomework(int h)               { hw_.push_back(h); }

    const std::string& name()    const { return name_; }
    const std::string& surname() const { return surname_; }

    double finalAverage() const;                // 0.4 * average(hw) + 0.6 * exam
    double finalMedian()  const;                // 0.4 * median(hw)  + 0.6 * exam

    friend std::istream& operator>>(std::istream& in, Person& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

private:
    std::string      name_, surname_;
    std::vector<int> hw_;
    int              exam_;
};

#endif