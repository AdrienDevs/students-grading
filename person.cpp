#include "person.h"
#include <algorithm>
#include <iomanip>

Person::Person() : name_(), surname_(), hw_(nullptr), n_(0), exam_(0), final_(0.0) {}

Person::Person(const Person& o)
    : name_(o.name_), surname_(o.surname_), hw_(nullptr), n_(o.n_),
      exam_(o.exam_), final_(o.final_) {
    if (n_ > 0) {
        hw_ = new int[n_];
        std::copy(o.hw_, o.hw_ + n_, hw_);      // deep copy
    }
}

Person& Person::operator=(const Person& o) {
    if (this == &o) return *this;               // self-assignment guard
    int* newHw = nullptr;
    if (o.n_ > 0) {
        newHw = new int[o.n_];
        std::copy(o.hw_, o.hw_ + o.n_, newHw);
    }
    delete[] hw_;                               // free old data only after the copy succeeded
    hw_ = newHw;
    n_ = o.n_;
    name_ = o.name_;
    surname_ = o.surname_;
    exam_ = o.exam_;
    final_ = o.final_;
    return *this;
}

Person::~Person() { delete[] hw_; }

void Person::calcFinalAverage() {
    double sum = 0;
    for (std::size_t i = 0; i < n_; ++i) sum += hw_[i];
    double hwAvg = n_ ? sum / n_ : 0.0;
    final_ = 0.4 * hwAvg + 0.6 * exam_;
}

std::istream& operator>>(std::istream& in, Person& p) {
    std::cout << "Name: ";                       in >> p.name_;
    std::cout << "Surname: ";                    in >> p.surname_;
    std::cout << "Number of homework results: "; in >> p.n_;
    delete[] p.hw_;
    p.hw_ = p.n_ ? new int[p.n_] : nullptr;
    for (std::size_t i = 0; i < p.n_; ++i) {
        std::cout << "HW" << i + 1 << ": ";
        in >> p.hw_[i];
    }
    std::cout << "Exam: ";                       in >> p.exam_;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << std::left << std::setw(12) << p.name_ << std::setw(15) << p.surname_
        << std::right << std::setw(18) << std::fixed << std::setprecision(2) << p.final_;
    return out;
}