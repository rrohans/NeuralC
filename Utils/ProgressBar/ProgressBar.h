#pragma once

#include <string>

class ProgressBar
{
private:
    int start, current, stop;
    double percentComplete;
    std::string buff = std::string(10, ' ');

public:
    ProgressBar(int begin = 0, int end = 100);

    void update(int newCurrent);

    void print();

    void print(const std::string& extra);

    ProgressBar *complete();

};