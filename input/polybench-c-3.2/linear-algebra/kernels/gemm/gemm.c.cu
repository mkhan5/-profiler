#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "gemm.h"

/* Header below added by Tulsi */
#include <stdlib.h>


/* Header below added by Tulsi for replaced CUBLAS code */
#include <cuda_blas.h>

extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
static void init_array(int ni, int nj, int nk, double *alpha, double *beta, double C[1024 + 0][1024 + 0], double A[1024 + 0][1024 + 0], double B[1024 + 0][1024 + 0])
{
  int i;
  int j;
  *alpha = 1;
  *beta = 0;
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++)
    C[i][j] = (((double) i) * j) / ni;


  for (i = 0; i < ni; i++)
    for (j = 0; j < nk; j++)
    A[i][j] = (((double) i) * j) / ni;


  for (i = 0; i < nk; i++)
    for (j = 0; j < nj; j++)
    B[i][j] = (((double) i) * j) / ni;


}

static void print_array(int ni, int nj, double C[1024 + 0][1024 + 0])
{
  int i;
  int j;
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++)
  {
    fprintf(stderr, "%0.2lf ", C[i][j]);
    if ((((i * ni) + j) % 20) == 0)
      fprintf(stderr, "\n");

  }


  fprintf(stderr, "\n");
}

static void kernel_gemm(int ni, int nj, int nk, double alpha, double beta, double C[1024 + 0][1024 + 0], double A[1024 + 0][1024 + 0], double B[1024 + 0][1024 + 0])
{
  int i;
  int j;
  int k;
  cublas_dgemm(A, B, C, ni, ni, ni, alpha);
}

int main(int argc, char **argv)
{
  int ni = 1024;
  int nj = 1024;
  int nk = 1024;
  double alpha;
  double beta;
  double (*C)[1024 + 0][1024 + 0];
  C = (double (*)[1024 + 0][1024 + 0]) polybench_alloc_data((1024 + 0) * (1024 + 0), sizeof(double));
  ;
  double (*A)[1024 + 0][1024 + 0];
  A = (double (*)[1024 + 0][1024 + 0]) polybench_alloc_data((1024 + 0) * (1024 + 0), sizeof(double));
  ;
  double (*B)[1024 + 0][1024 + 0];
  B = (double (*)[1024 + 0][1024 + 0]) polybench_alloc_data((1024 + 0) * (1024 + 0), sizeof(double));
  ;
  init_array(ni, nj, nk, &alpha, &beta, *C, *A, *B);
  ;
  kernel_gemm(ni, nj, nk, alpha, beta, *C, *A, *B);
  ;
  ;
  if ((argc > 42) && (!strcmp(argv[0], "")))
    print_array(ni, nj, *C);

  free((void *) C);
  ;
  free((void *) A);
  ;
  free((void *) B);
  ;
  return 0;
}

