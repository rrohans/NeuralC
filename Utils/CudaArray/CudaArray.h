#pragma once

#include <cuda_runtime.h>
#include "device_launch_parameters.h"


template <typename T>
class Cuda_Array
{
private:

	T* begin = nullptr; 
	T* end = nullptr;

	void alloc(size_t size)
	{
		// allocate memory on the gpu and check for success
		cudaError_t error = cudaMalloc((void**)&begin, size * sizeof(T));

		if (error != cudaSuccess)
		{
			begin = nullptr;
			end = nullptr;
			printf("Failed to allocate memory on the GPU- CUDA Error: %d\n", error);
			exit(EXIT_FAILURE);
		}

		end = begin + size;
	}
	
	void freeMemory()
	{

		if (begin != nullptr)
		{
			cudaDeviceSynchronize();
			cudaFree(begin);
			begin = nullptr;
			end = nullptr;
		}
	}

public:

	Cuda_Array() {}
	~Cuda_Array() { freeMemory(); }

	void resize(size_t size)
	{
		freeMemory();
		alloc(size);
	}

	size_t getSize() const
	{
		// return size of array
		return end - begin;
	}

	T* getData() const
	{
		// return pointer to first element
		return begin;
	}

	void set(T* src, size_t size)
	{
		// copy data from source to cuda array

		if (size != getSize() && begin != nullptr)
		{
			printf("Size mismatch\n");
			exit(EXIT_FAILURE);
		}

		resize(size);

		cudaError_t error = cudaMemcpy(begin, src, size * sizeof(T), cudaMemcpyHostToDevice);
		
		if (error != cudaSuccess)
		{
			printf("Failed to set memory on the GPU- CUDA Error: %d\n", error);
			exit(EXIT_FAILURE);
		}
	}

	void get(T* dest, size_t size)
	{
		// copy data from cuda array to dest

		if (size != getSize())
		{
			printf("Size mismatch\n");
			exit(EXIT_FAILURE);
		}

		cudaError_t error = cudaMemcpy(dest, begin, size * sizeof(T), cudaMemcpyDeviceToHost);
		
		if (error != cudaSuccess)
		{
			printf("Failed to get memory from the GPU - CUDA Error: %d\n", error);
			exit(EXIT_FAILURE);
		}
	}

};