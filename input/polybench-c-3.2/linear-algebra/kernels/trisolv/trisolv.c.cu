#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "trisolv.h"

/* Header below added by Tulsi */
#include <stdlib.h>


/* Header below added by Qahwa for replaced CUBLAS code */
#include <cublas_v2.h>

extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
static void init_array(int n, double A[4000 + 0][4000 + 0], double x[4000 + 0], double c[4000 + 0])
{
  int i;
  int j;
  for (i = 0; i < n; i++)
  {
    c[i] = (x[i] = ((double) i) / n);
    for (j = 0; j < n; j++)
      A[i][j] = (((double) i) * j) / n;

  }

}

static void print_array(int n, double x[4000 + 0])
{
  int i;
  for (i = 0; i < n; i++)
  {
    fprintf(stderr, "%0.2lf ", x[i]);
    if ((i % 20) == 0)
      fprintf(stderr, "\n");

  }

}

static void kernel_trisolv(int n, double A[4000 + 0][4000 + 0], double x[4000 + 0], double c[4000 + 0])
{
  int i;
  int j;
  float *a_d;
  float *b_d;
  cudaMalloc(&a_d, (n * n) * (sizeof(float)));
  cudaMalloc(&b_d, n * (sizeof(float)));
  cudaMemcpy(b_d, c, n * (sizeof(float)), cudaMemcpyHostToDevice);
  cudaMemcpy(a_d, A, (n * n) * (sizeof(float)), cudaMemcpyHostToDevice);
  const float alpha = 1.0f;
  cublasStrsm(handle, CUBLAS_SIDE_LEFT, CUBLAS_FILL_MODE_LOWER, CUBLAS_OP_N, CUBLAS_DIAG_UNIT, n, 1, &alpha, A, n, c, n);
  cudaMemcpy(x, b_d, n * (sizeof(float)), cudaMemcpyDeviceToHost);
  cudaFree(A_d);
  cudaFree(b_d);
  cublasDestroy(handle);
}

int main(int argc, char **argv)
{
  int n = 4000;
  double (*A)[4000 + 0][4000 + 0];
  A = (double (*)[4000 + 0][4000 + 0]) polybench_alloc_data((4000 + 0) * (4000 + 0), sizeof(double));
  ;
  double (*x)[4000 + 0];
  x = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*c)[4000 + 0];
  c = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  init_array(n, *A, *x, *c);
  ;
  kernel_trisolv(n, *A, *x, *c);
  ;
  ;
  if ((argc > 42) && (!strcmp(argv[0], "")))
    print_array(n, *x);

  free((void *) A);
  ;
  free((void *) x);
  ;
  free((void *) c);
  ;
  return 0;
}

