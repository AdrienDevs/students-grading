#include "person.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>

Person::Person() : name_(), surname_(), hw_(), exam_(0) {}

Person::Person(const Person& o)
    : name_(o.name_), surname_(o.surname_), hw_(o.hw_), exam_(o.exam_) {}

Person& Person::operator=(const Person& o) {
    if (this != &o) {
        name_ = o.name_;
        surname_ = o.surname_;
        hw_ = o.hw_;
        exam_ = o.exam_;
    }
    return *this;
}

Person::~Person() {}

bool Person::parseLine(const std::string& line) {
    std::istringstream ss(line);                // skips any spaces/tabs and a trailing '\r'
    if (!(ss >> name_ >> surname_)) return false;
    std::vector<int> nums;
    int x;
    while (ss >> x) nums.push_back(x);
    if (nums.empty()) return false;             // no exam -> invalid line
    exam_ = nums.back();                        // last number = exam
    nums.pop_back();
    hw_ = std::move(nums);                      // the rest = homework
    return true;
}

double Person::finalAverage() const {
    double avg = hw_.empty() ? 0.0
               : std::accumulate(hw_.begin(), hw_.end(), 0.0) / hw_.size();
    return 0.4 * avg + 0.6 * exam_;
}

double Person::finalMedian() const {
    if (hw_.empty()) return 0.6 * exam_;
    std::vector<int> tmp(hw_);
    std::sort(tmp.begin(), tmp.end());
    std::size_t n = tmp.size();
    double med = (n % 2) ? tmp[n / 2] : (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
    return 0.4 * med + 0.6 * exam_;
}

std::istream& operator>>(std::istream& in, Person& p) {
    p.hw_.clear();
    std::cout << "Name: ";    in >> p.name_;
    std::cout << "Surname: "; in >> p.surname_;
    std::cout << "Homework results (type 0 to finish): ";
    int h;
    while (in >> h && h != 0) p.hw_.push_back(h);
    in.clear();
    std::cout << "Exam: "; in >> p.exam_;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << std::left << std::setw(14) << p.name_ << std::setw(16) << p.surname_;
    return out;
}