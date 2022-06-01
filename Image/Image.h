#pragma once

#include "../Matrix/Matrix.h"

struct Image
{
    int label;
    Matrix imageData;

    // member methods
    void print() const;

    static Image **readDataset(const std::string &fileName, int numberOfImages);
};