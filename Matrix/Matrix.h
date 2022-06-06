#pragma once

#include <string>
#include <vector>

struct Matrix
{
    // member variables
    int numRows = 0, numCols = 0;
    std::vector<std::vector<float>> data;

    // constructors/destructors
    Matrix();

    Matrix(int rows, int cols);

    explicit Matrix(const std::string &fileName);

    explicit Matrix(int size);

    // member methods
    void create();

    void fill(float n);

    void print() const;

    void save(const std::string &fileName) const;

    void load(const std::string &fileName);

    void flatten(int axis);

    int argMax() const;

    void zeros();

    void ones();

    void eye();

    void randomize(int n);

    void copy(Matrix m);

    float operator() (int i, int j);

};