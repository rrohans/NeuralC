#pragma once

#include <chrono>

using namespace std::chrono;

// Class that creates an object that can report the time
// it takes for a function to execute. Once object is destructed
// Time is calculated from start of function to exit of scope.

class ScopedTimer
{
private:
    high_resolution_clock::time_point start;
    std::string name;

public:
    explicit ScopedTimer(const std::string &_name);

    ~ScopedTimer();
};