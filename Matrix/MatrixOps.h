#pragma once

#include "Matrix.h"

namespace MatrixOps
{
    bool verifyDimensions(Matrix &m1, Matrix &m2);

    float uniformDist(float min, float max);

    Matrix add(Matrix &m1, Matrix &m2);

    Matrix subtract(Matrix &m1, Matrix &m2);

    Matrix hadamard(Matrix &m1, Matrix &m2);

    Matrix multiply(Matrix &m1, Matrix &m2);

    Matrix transform(float (*f)(float), Matrix &m);

    Matrix addScalar(Matrix &m, float c);

    Matrix scale(Matrix &m, float c);

    Matrix transpose(Matrix &m);

}