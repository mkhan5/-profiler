#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "atax.h"

/* Header below added by Tulsi */
#include <stdlib.h>


/* Header below added by Qahwa for replaced CUBLAS code */
#include <cublas_v2.h>

extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
static void init_array(int nx, int ny, double A[4000 + 0][4000 + 0], double x[4000 + 0])
{
  int i;
  int j;
  for (i = 0; i < ny; i++)
    x[i] = i * M_PI;

  for (i = 0; i < nx; i++)
    for (j = 0; j < ny; j++)
    A[i][j] = (((double) i) * (j + 1)) / nx;


}

static void print_array(int nx, double y[4000 + 0])
{
  int i;
  for (i = 0; i < nx; i++)
  {
    fprintf(stderr, "%0.2lf ", y[i]);
    if ((i % 20) == 0)
      fprintf(stderr, "\n");

  }

  fprintf(stderr, "\n");
}

static void kernel_atax(int nx, int ny, double A[4000 + 0][4000 + 0], double x[4000 + 0], double y[4000 + 0], double tmp[4000 + 0])
{
  int i;
  int j;
  for (i = 0; i < nx; i++)
    y[i] = 0;

  float *a_d;
  float *x_d;
  cudaMalloc(&a_d, (nx * nx) * (sizeof(float)));
  cudaMalloc(&x_d, nx * (sizeof(float)));
  cudaMemcpy(x_d, x, nx * (sizeof(float)), cudaMemcpyHostToDevice);
  cudaMemcpy(a_d, A, (nx * nx) * (sizeof(float)), cudaMemcpyHostToDevice);
  const float alpha = 1.0f;
  const float beta = 0.0;
  cublasSgemv(handle, CUBLAS_OP_T, nx, nx, &alpha, A, nx, x, 1, &beta, y, 1);
  cublasSgemv(handle, CUBLAS_OP_N, nx, nx, &alpha, A, nx, y, 1, &beta, _result[1], 1);
  cudaMemcpy(y, y, nx * (sizeof(float)), cudaMemcpyDeviceToHost);
  cudaFree(a_d);
  cudaFree(x_d);
  cublasDestroy(handle);
}

int main(int argc, char **argv)
{
  int nx = 4000;
  int ny = 4000;
  double (*A)[4000 + 0][4000 + 0];
  A = (double (*)[4000 + 0][4000 + 0]) polybench_alloc_data((4000 + 0) * (4000 + 0), sizeof(double));
  ;
  double (*x)[4000 + 0];
  x = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*y)[4000 + 0];
  y = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*tmp)[4000 + 0];
  tmp = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  init_array(nx, ny, *A, *x);
  ;
  kernel_atax(nx, ny, *A, *x, *y, *tmp);
  ;
  ;
  if ((argc > 42) && (!strcmp(argv[0], "")))
    print_array(nx, *y);

  free((void *) A);
  ;
  free((void *) x);
  ;
  free((void *) y);
  ;
  free((void *) tmp);
  ;
  return 0;
}

