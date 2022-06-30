#include <cmath>

#include "Activations.h"

float Activations::sigmoid(float a)
{
    // compute the value using the sigmoid function:
    // f(n) = 1 / (1 + e^(-n))
    return 1.0f / (1 + std::exp(-1 * a));
}

float Activations::sigmoidPrime(float a)
{
    // s(n) * (1 - s(n))
    float sa = sigmoid(a);
    return sa * (1 - sa);
}

float Activations::relu(float a)
{
    // activation function based on Rectified Linear Unit
    return a >= 0 ? a : 0;
}

float Activations::reluPrime(float a)
{
    // activation function based on Rectified Linear Unit
    return a >= 0 ? 1 : 0;
}

Matrix Activations::sigmoidPrimeValues(Matrix &m)
{
    // create a matrix whose values are computed as follows
    // s(n) * (1 - s(n))

    Matrix ones(m.numRows, m.numCols);
    ones.ones();

    MatrixOps::map(sigmoid, m);

    auto subtracted = MatrixOps::subtract(ones, m);

    return MatrixOps::elementwiseMultiply(m, subtracted);
}

Matrix Activations::softmax(Matrix &m)
{
    float sum = 0.0f;

    for (int i = 0; i < m.numRows * m.numCols; i++)
        sum += std::exp(m.data[i]);

    Matrix result(m.numRows, m.numCols);

    for (int i = 0; i < result.numRows * result.numCols; i++)
        result.data[i] = std::exp(m.data[i]) / sum;

    return result;
}