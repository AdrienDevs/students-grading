#ifndef TIMER_H
#define TIMER_H

#include <chrono>

// Stopwatch based on a monotonic clock (never jumps backwards, unlike system_clock).
class Timer {
public:
    Timer() : start_(clock::now()) {}
    void reset() { start_ = clock::now(); }
    double elapsed() const {                    // seconds since construction / last reset()
        return std::chrono::duration<double>(clock::now() - start_).count();
    }
private:
    using clock = std::chrono::steady_clock;
    clock::time_point start_;
};

#endif