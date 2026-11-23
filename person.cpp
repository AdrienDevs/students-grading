#include "person.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <utility>

Person::Person() : name_(), surname_(), hw_(), exam_(0), finalAvg_(0.0), finalMed_(0.0) {}

Person::Person(const Person& o)
    : name_(o.name_), surname_(o.surname_), hw_(o.hw_), exam_(o.exam_),
      finalAvg_(o.finalAvg_), finalMed_(o.finalMed_) {}

Person& Person::operator=(const Person& o) {
    if (this != &o) {
        name_ = o.name_;
        surname_ = o.surname_;
        hw_ = o.hw_;
        exam_ = o.exam_;
        finalAvg_ = o.finalAvg_;
        finalMed_ = o.finalMed_;
    }
    return *this;
}

Person::~Person() {}

Person::Person(Person&& o) noexcept
    : name_(std::move(o.name_)), surname_(std::move(o.surname_)), hw_(std::move(o.hw_)),
      exam_(o.exam_), finalAvg_(o.finalAvg_), finalMed_(o.finalMed_) {}

Person& Person::operator=(Person&& o) noexcept {
    if (this != &o) {
        name_ = std::move(o.name_);
        surname_ = std::move(o.surname_);
        hw_ = std::move(o.hw_);
        exam_ = o.exam_;
        finalAvg_ = o.finalAvg_;
        finalMed_ = o.finalMed_;
    }
    return *this;
}

void Person::calcFinals() {
    if (hw_.empty()) {
        finalAvg_ = finalMed_ = 0.6 * exam_;
        return;
    }
    double avg = std::accumulate(hw_.begin(), hw_.end(), 0.0) / hw_.size();
    std::vector<int> tmp(hw_);                      // sort a copy, keep the original order
    std::sort(tmp.begin(), tmp.end());
    std::size_t n = tmp.size();
    double med = (n % 2) ? tmp[n / 2] : (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
    finalAvg_ = 0.4 * avg + 0.6 * exam_;
    finalMed_ = 0.4 * med + 0.6 * exam_;
}

void Person::parseLine(const std::string& line) {
    std::istringstream ss(line);                    // skips spaces/tabs and a trailing '\r'
    std::string name, surname;
    if (!(ss >> name >> surname))
        throw std::invalid_argument("missing name or surname");

    std::vector<int> nums;
    int x;
    while (ss >> x) {
        if (x < 0 || x > 10)
            throw std::out_of_range("grade out of range 0-10: " + std::to_string(x));
        nums.push_back(x);
    }
    if (!ss.eof())                                  // the loop stopped on something that is not a number
        throw std::invalid_argument("a grade is not a number");
    if (nums.empty())
        throw std::invalid_argument("missing exam result");

    name_ = std::move(name);
    surname_ = std::move(surname);
    exam_ = nums.back();                            // last number = exam
    nums.pop_back();
    hw_ = std::move(nums);                          // the rest = homework
    calcFinals();
}

// Interactive input: the user decides when the homework list ends (0 = finished).
std::istream& operator>>(std::istream& in, Person& p) {
    p.hw_.clear();
    std::cout << "Name: ";    in >> p.name_;
    std::cout << "Surname: "; in >> p.surname_;
    std::cout << "Homework results (type 0 to finish): ";
    int h;
    while (in >> h && h != 0) p.hw_.push_back(h);
    in.clear();
    std::cout << "Exam: "; in >> p.exam_;
    p.calcFinals();
    return in;
}

// Prints name and surname only; the caller prints the numbers it needs.
std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << std::left << std::setw(14) << p.name_ << std::setw(16) << p.surname_;
    return out;
}