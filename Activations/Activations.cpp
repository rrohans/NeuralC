#include <cmath>

#include "Activations.h"

float Activations::sigmoid(float a)
{
    // compute the value using the sigmoid function:
    // f(n) = 1 / (1 + e^(-n))
    return 1.0f / (1 + exp(-1 * a));
}

float Activations::relu(float a)
{
    // activation function based on Rectified Linear Unit
    return a > 0 ? a : 0;
}

Matrix Activations::sigmoidPrimeValues(Matrix &m)
{
    // create a matrix whose values are computed as follows
    // s(n) * (1 - s(n))

    Matrix ones(m.numRows, m.numCols);
    ones.ones();

    MatrixOps::transform(sigmoid, m);

    auto subtracted = MatrixOps::subtract(ones, m);

    return MatrixOps::hadamard(m, subtracted);
}

Matrix Activations::softmax(Matrix &m)
{
    float sum = 0.0f;

    for (int i = 0; i < m.numRows; i++)
        for (int j = 0; j < m.numCols; j++)
            sum += exp(m.data[i][j]);

    Matrix result(m.numRows, m.numCols);

    for (int i = 0; i < result.numRows; i++)
        for (int j = 0; j < result.numCols; j++)
            result.data[i][j] = exp(m.data[i][j]) / sum;

    return result;
}