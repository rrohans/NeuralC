#include <iostream>
#include <chrono>

#include "ScopedTimer.h"

using namespace std::chrono;

ScopedTimer::ScopedTimer(const std::string &_name)
{
    start = high_resolution_clock::now();
    name = _name;
}

ScopedTimer::~ScopedTimer()
{
    auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start);
    std::cout << name << " took " << duration.count() << " milliseconds\n";
}
