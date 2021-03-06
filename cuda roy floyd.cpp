#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include "stdafx.h"

__device__ int min(int a, int b)
{
		if (a > b)
		return a;
	else
		return b;
}

__global__ void RoyFloyd(int a[n][n], int k) 
	{
	
	int i = threadIdx.x;
	int j = threadIdx.y;
	
	a[i][j] = min(a[i][j], a[i][k] + a[k][j]);

	}

int main()
{
	int INFINIT = 9999;
	int n = 5;

	size_t size = n * n * sizeof(float); 



	int h_a[n][n] = { { 0, 2, INFINIT, 2, INFINIT },
					{  2, 0, 3, INFINIT, INFINIT },
					{ INFINIT, 3, 0, 1, 8 },
					{ 10, INFINIT, 1, 0, INFINIT },
					{ INFINIT, INFINIT, 8, INFINIT, 0 } }; 



	int* d_a; 

	cudaMalloc(&d_a, size);

	cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice); 
	
	int numBlocks = 1;

	dim3 threadsPerBlock(n*n);



	for (int k = 0; k < n; k++) 
		RoyFloyd << <numBlocks, threadsPerBlock >> >(d_a, k);


	cudaMemcpy(h_a, d_a, size, cudaMemcpyDeviceToHost);
	
	for (x = 0; x < n; x++) {

		for (y = 0; y < n; y++)
			printf("%d     ", h_a[x][y]);

		printf("\n");
		}
	cudaFree(d_a);
	free(h_a);
	return 0;
	}
