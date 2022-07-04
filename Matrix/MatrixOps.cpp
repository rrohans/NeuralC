
#include "MatrixOps.h"

#define RANDOM_SCALE 1000

bool MatrixOps::verifyDimensions(Matrix &m1, Matrix &m2)
{
    // verify that matrices are of the same dimensions
    return (m1.numRows == m2.numRows) && (m1.numCols == m2.numCols);
}

Matrix MatrixOps::add(Matrix &m1, Matrix &m2)
{
    // perform elementwise addition
    if (!verifyDimensions(m1, m2))
    {
        printf("Dimension mismatch %dx%d %dx%d", m1.numRows, m1.numCols, m2.numRows, m2.numCols);
        exit(EXIT_FAILURE);
    }

    Matrix result(m1.numRows, m1.numCols);

    for (int i = 0; i < m1.numRows * m1.numCols; i++)
        result.data[i] = m1.data[i] + m2.data[i];

    return result;
}

Matrix MatrixOps::subtract(Matrix &m1, Matrix &m2)
{
    // perform elementwise subtraction
    if (!verifyDimensions(m1, m2))
    {
        printf("Dimension mismatch %dx%d %dx%d", m1.numRows, m1.numCols, m2.numRows, m2.numCols);
        exit(EXIT_FAILURE);
    }

    Matrix result(m1.numRows, m1.numCols);

    for (int i = 0; i < m1.numRows * m1.numCols; i++)
        result.data[i] = m1.data[i] - m2.data[i];

    return result;
}

Matrix MatrixOps::elementwiseMultiply(Matrix &m1, Matrix &m2)
{
    // perform elementwise multiplication
    if (!verifyDimensions(m1, m2))
    {
        printf("Dimension mismatch %dx%d %dx%d", m1.numRows, m1.numCols, m2.numRows, m2.numCols);
        exit(EXIT_FAILURE);
    }

    Matrix result(m1.numRows, m1.numCols);

    for (int i = 0; i < m1.numRows * m1.numCols; i++)
        result.data[i] = m1.data[i] * m2.data[i];

    return result;
}

Matrix MatrixOps::multiply(Matrix &m1, Matrix &m2)
{
    // perform matrix multiplication
    if (m1.numCols != m2.numRows)
    {
        printf("Dimension mismatch %dx%d %dx%d", m1.numRows, m1.numCols, m2.numRows, m2.numCols);
        exit(EXIT_FAILURE);
    }

    Matrix result(m1.numRows, m2.numCols);

    for (int i = 0; i < m1.numRows; i++)
        for (int j = 0; j < m2.numCols; j++)
        {
            float sum = 0.0f;
            for (int k = 0; k < m2.numRows; k++)
                sum += m1.data[i * m1.numCols + k] * m2.data[k * m2.numCols + j];

            result.data[i * result.numCols + j] = sum;
        }

    return result;
}

Matrix MatrixOps::map(float (*f)(float), Matrix &m)
{
    // apply a transformation function to each element
    // of the matrix
    Matrix result(m.numRows, m.numCols);

    for (int i = 0; i < m.numRows * m.numCols; i++)
        result.data[i] = (*f)(m.data[i]);

    return result;
}

Matrix MatrixOps::add(Matrix &m, float c)
{
    // add a scalar to each element
    Matrix result(m.numRows, m.numCols);

    for (int i = 0; i < m.numRows * m.numCols; i++)
        result.data[i] = m.data[i] + c;

    return result;
}

Matrix MatrixOps::scale(Matrix &m, float c)
{
    //  scale each element
    Matrix result(m.numRows, m.numCols);

    for (int i = 0; i < m.numRows * m.numCols; i++)
        result.data[i] = m.data[i] * c;

    return result;
}

Matrix MatrixOps::transpose(Matrix &m)
{
    // transpose a given matrix
    Matrix result(m.numCols, m.numRows);

    int rows = m.numRows;
    int cols = m.numCols;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[j * cols + i] = m.data[i * cols + j];

    return result;
}

float MatrixOps::uniformDist(float min, float max)
{
    // fill matrix with random numbers between min and max
    float range = max - min;
    int scaledRange = int(range * RANDOM_SCALE);

    return min + (float) (rand() % scaledRange) / RANDOM_SCALE;
}