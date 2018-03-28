#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Header below added by Tulsi */
#include <stdlib.h>


/* Header below added by Qahwa for replaced CUBLAS code */
#include <cublas_v2.h>

int N = 3;
void symm(float alpha, float beta, float A[N][N], float B[N][N], float C[N][N])
{
  int i;
  int j;
  int k;
  float temp2;
  float *a_d;
  float *x_d;
  cudaMalloc(&a_d, (N * N) * (sizeof(float)));
  cudaMalloc(&b_d, (N * N) * (sizeof(float)));
  cudaMemcpy(a_d, A, (N * N) * (sizeof(float)), cudaMemcpyHostToDevice);
  cudaMemcpy(b_d, B, (N * N) * (sizeof(float)), cudaMemcpyHostToDevice);
  const float alpha = 1.0f;
  const float beta = 0.0f;
  cublasSsymm(CblasRowMajor, CUBLAS_SIDE_RIGHT, CUBLAS_FILL_MODE_LOWER, N, N, alpha, A, N, B, N, beta, C, N);
  cudaMemcpy(c, C, (N * N) * (sizeof(float)), cudaMemcpyDeviceToHost);
  cudaFree(a_d);
  cudaFree(b_d);
  cublasDestroy(handle);
}

int main(int argc, char **argv)
{
  int M = 3;
  int n = N;
  float alpha = 1;
  float beta = 0;
  float a[3][3] = {1, 0, 0, 2, 5, 0, 3, 6, -3};
  float b[3][3] = {1, 0, 1, 3, -1, -2, 0, 2, -1};
  float res[3][3];
  symm(alpha, beta, a, b, res);
  int i;
  int j;
  printf("The res x is \n");
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      printf(" %f ", res[i][j]);
    }

    printf("\n");
  }

  printf("\n");
}

