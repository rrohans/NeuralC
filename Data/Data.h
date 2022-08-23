#pragma once

#include <vector>

#include "../Matrix/Matrix.h"

struct Data
{
    int label{};
    Matrix imageData;

    Data(int rows, int cols);

    // member methods
    void print() const;

    static std::vector<Data> readDataset(const std::string &fileName, int rows = 28, int cols = 28);

    static void readDataset(const std::string &fileName, std::vector<Data> &images, int rows = 28, int cols = 28);
};