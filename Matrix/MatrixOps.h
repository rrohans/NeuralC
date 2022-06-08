#pragma once

#include "Matrix.h"

namespace MatrixOps
{
    bool verifyDimensions(Matrix &m1, Matrix &m2);

    float uniformDist(float min, float max);

    Matrix add(Matrix &m1, Matrix &m2);

    Matrix subtract(Matrix &m1, Matrix &m2);

    Matrix elementwiseMultiply(Matrix &m1, Matrix &m2);

    Matrix multiply(Matrix &m1, Matrix &m2);

    Matrix cudaMultiply(Matrix& m1, Matrix& m2);

    Matrix map(float (*f)(float), Matrix &m);

    Matrix add(Matrix &m, float c);

    Matrix scale(Matrix &m, float c);

    Matrix transpose(Matrix &m);

}