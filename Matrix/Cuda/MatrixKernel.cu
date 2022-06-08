
#include <cmath>
#include <iostream>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "MatrixKernel.h"

#define TILE_DIM 16


__global__ void cudaMatrixMultiplyKernel(float* a, float* b, float* c, int aRows, int aCols, int bRows, int bCols, int cRows, int cCols)
{
	int row = blockIdx.y * TILE_DIM + threadIdx.y;
	int col = blockIdx.x * TILE_DIM + threadIdx.x;

	float temp = 0;

	for (int i = 0; i < (TILE_DIM + aCols - 1) / TILE_DIM; i++)
		for (int j = 0; j < TILE_DIM; ++j)
			if ((i * TILE_DIM + j < aCols && row < aRows) && (i * TILE_DIM + j < bRows && col < bCols))
				temp += a[row * aCols + i * TILE_DIM + j] * b[(i * TILE_DIM + j) * bCols + col];

	if (row < cRows && col < cCols)
		c[((blockIdx.y * blockDim.y + threadIdx.y) * cCols) + (blockIdx.x * blockDim.x) + threadIdx.x] = temp;

}

void cudaMatrixMultiply(float* a, float* b, float* c, int aRows, int aCols, int bRows, int bCols, int cRows, int cCols)
{
	dim3 dimBlock(TILE_DIM, TILE_DIM, 1);
	dim3 dimGrid;

	dimGrid.x = (cCols + dimBlock.x - 1) / dimBlock.x;
	dimGrid.y = (cRows + dimBlock.y - 1) / dimBlock.y;

	cudaMatrixMultiplyKernel << <dimGrid, dimBlock >> > (a, b, c, aRows, aCols, bRows, bCols, cRows, cCols);
}