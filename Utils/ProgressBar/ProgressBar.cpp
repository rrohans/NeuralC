#include "ProgressBar.h"

#include <cmath>

ProgressBar::ProgressBar(int begin, int end)
{
    start = begin;
    current = begin;
    stop = end;
    percentComplete = 0.0;
}

void ProgressBar::update(int newCurrent)
{
    current = newCurrent;
    percentComplete = current / double(stop - start);

    // set number of starts in buffer
    for (int i = 0; i < floor(percentComplete * 10); i++)
        buff[i] = '=';
}

void ProgressBar::print()
{
    printf("\33[2K\r");
    printf("[%s] - %.0lf%% complete\n", buff.c_str(), percentComplete * 100);
}

ProgressBar *ProgressBar::complete()
{
    update(stop);
    return this;
}

void ProgressBar::print(const std::string& extra)
{
    printf("\33[2K\r");
    printf("[%s] - %.0lf%% complete - %s\n", buff.c_str(), percentComplete * 100, extra.c_str());
}
