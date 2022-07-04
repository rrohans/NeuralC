#include <iostream>
#include <fstream>
#include <istream>
#include <cmath>

#include "Matrix.h"
#include "MatrixOps.h"

Matrix::Matrix(int rows, int cols)
{
    numRows = rows;
    numCols = cols;

    data = std::vector<float>(numRows * numCols);

    // set data entries to 0
    for (int i = 0; i < numRows * numCols; i++)
        data[i] = 0;
}

Matrix::Matrix(const std::string &fileName)
{
    load(fileName);
}

Matrix::Matrix(int size)
{
    // create an identity matrix with given size
    numRows = size;
    numCols = size;

    data = std::vector<float>(numRows * numCols);

    eye();
}

void Matrix::fill(float n)
{
    // fill matrix with provided value
    for (int i = 0; i < numRows * numCols; i++)
        data[i] = n;
}

void Matrix::print() const
{
    // print matrix
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            printf("%.2lf ", data[i * numCols + j]);
        }
        printf("\n");
    }
}

void Matrix::save(const std::string &fileName) const
{
    // write contents of matrix to file as a binary

    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    if (!file)
    {
        printf("Error creating file: %s\n", fileName.c_str());
        exit(EXIT_FAILURE);
    }

    // write dimensions of matrix
    file.write((char *) &numRows, sizeof(int));
    file.write((char *) &numCols, sizeof(int));

    // write data of matrix
    for (int i = 0; i < numRows * numCols; i++)
        file.write((char *) &data[i], sizeof(float));

    file.close();

    if (!file.good())
    {
        printf("Error writing to file: %s\n", fileName.c_str());
        exit(EXIT_FAILURE);
    }
}

void Matrix::load(const std::string &fileName)
{
    // load matrix from a file
    std::ifstream file(fileName, std::ios::in | std::ios::binary);

    if (!file)
    {
        printf("Error opening file: %s\n", fileName.c_str());
        exit(EXIT_FAILURE);
    }

    file.read((char *) &numRows, sizeof(int));
    file.read((char *) &numCols, sizeof(int));

    // set data pointer if equal to null
    create();

    for (int i = 0; i < numRows * numCols; i++)
        file.read((char *) &data[i], sizeof(float));

    file.close();

    if (!file.good())
    {
        printf("Error writing from file: %s\n", fileName.c_str());
        exit(EXIT_FAILURE);
    }
}

void Matrix::flatten(int axis)
{
    // flatten matrix into single column or row
    // 0 -> row, 1-> col

    if (axis != 0 && axis != 1)
    {
        printf("Error Invalid dimension: %d\n", axis);
        exit(EXIT_FAILURE);
    }

    if (axis == 0)
    {
        int numOfEntries = numRows * numCols;

        numRows = numOfEntries;
        numCols = 1;

    } else
    {
        int numOfEntries = numRows * numCols;

        numRows = 1;
        numCols = numOfEntries;

    }
}

int Matrix::argMax() const
{
    // return index of the largest value
    // valid only for column matrix

    if (numCols != 1)
    {
        printf("Matrix is not a column Matrix\n");
        exit(EXIT_FAILURE);
    }

    int maxIndex = 0;

    for (int i = 0; i < numRows * numCols; i++)
        if (data[maxIndex] < data[i])
            maxIndex = i;

    return maxIndex;
}

void Matrix::zeros()
{
    // fill values with 0
    fill(0);
}

void Matrix::ones()
{
    // fill values with 1
    fill(1);
}

void Matrix::eye()
{
    // create an identity matrix
    // only works with square matrix

    if (numRows != numCols)
    {
        printf("Matrix is not a square matrix %dx%d", numRows, numCols);
        exit(EXIT_FAILURE);
    }

    zeros();

    for (int i = 0; i < numRows; i++)
        data[i * numCols + i] = 1;
}


void Matrix::randomize(int n)
{
    // randomize the entries for the matrix
    // values will range from -1/sqrt(n) to 1/sqrt(n)
    for (int i = 0; i < numRows * numCols; i++)
        data[i] = MatrixOps::uniformDist(float(-1 / sqrt(n)), float(1 / sqrt(n)));
}

void Matrix::copy(Matrix m)
{
    // Copy data from other matrix into current matrix
    if (!MatrixOps::verifyDimensions(*this, m))
    {
        printf("Dimension mismatch %dx%d %dx%d", this->numRows, this->numCols, m.numRows, m.numCols);
        exit(EXIT_FAILURE);
    }

    numRows = m.numRows;
    numCols = m.numCols;

    for (int i = 0; i < numRows * numCols; i++)
        data[i] = m.data[i];
}

float Matrix::operator()(int i, int j)
{
    return data[i * numCols + j];
}

void Matrix::create()
{
    data = std::vector<float>(numCols * numRows);
}


Matrix::Matrix() = default;
