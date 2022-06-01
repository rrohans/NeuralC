#pragma once

#include "../Matrix/Matrix.h"
#include "../Matrix/MatrixOps.h"

namespace Activations
{
    float sigmoid(float a);

    float relu(float a);

    Matrix sigmoidPrimeValues(Matrix &m);

    Matrix softmax(Matrix &m);
}