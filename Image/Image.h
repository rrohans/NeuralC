#pragma once

#include "../Matrix/Matrix.h"

struct Image
{
    int label{};
    Matrix imageData;

    Image(int rows, int cols);

    // member methods
    void print() const;

    static Image **readDataset(const std::string &fileName, int numberOfImages, int rows = 28, int cols = 28);
};