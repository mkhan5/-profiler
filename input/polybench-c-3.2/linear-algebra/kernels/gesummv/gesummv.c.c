#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "gesummv.h"

/* Header below added by Tulsi */
#include <stdlib.h>


/* Header below added by Qahwa for replaced OpenMP code */
#include <omp.h>
#include <mkl.h>

extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
static void init_array(int n, double *alpha, double *beta, double A[4000 + 0][4000 + 0], double B[4000 + 0][4000 + 0], double x[4000 + 0])
{
  int i;
  int j;
  *alpha = 1;
  *beta = 1;
  for (i = 0; i < n; i++)
  {
    x[i] = ((double) i) / n;
    for (j = 0; j < n; j++)
    {
      A[i][j] = (((double) i) * j) / n;
      B[i][j] = (((double) i) * j) / n;
    }

  }

}

static void print_array(int n, double y[4000 + 0])
{
  int i;
  for (i = 0; i < n; i++)
  {
    fprintf(stderr, "%0.2lf ", y[i]);
    if ((i % 20) == 0)
      fprintf(stderr, "\n");

  }

}

static void kernel_gesummv(int n, double alpha, double beta, double A[4000 + 0][4000 + 0], double B[4000 + 0][4000 + 0], double tmp[4000 + 0], double x[4000 + 0], double y[4000 + 0])
{
  int i;
  int j;
  double *z;
  z = (double *) mkl_malloc(n * (sizeof(double)), 64);
  for (i = 0; i < n; i++)
  {
    y[i] = 0.0;
    z[i] = 0.0;
  }

  cblas_dgemv(CblasRowMajor, CblasNoTrans, n, n, 1, A, n, x, 1, 1, y, 1);
  cblas_dgemv(CblasRowMajor, CblasTrans, n, n, 1, B, n, x, 1, 1, _result[1], 1);
  cblas_daxpby(n, alf, y, 1, bt, _result[1], 1);
}

int main(int argc, char **argv)
{
  int n = 4000;
  double alpha;
  double beta;
  double (*A)[4000 + 0][4000 + 0];
  A = (double (*)[4000 + 0][4000 + 0]) polybench_alloc_data((4000 + 0) * (4000 + 0), sizeof(double));
  ;
  double (*B)[4000 + 0][4000 + 0];
  B = (double (*)[4000 + 0][4000 + 0]) polybench_alloc_data((4000 + 0) * (4000 + 0), sizeof(double));
  ;
  double (*tmp)[4000 + 0];
  tmp = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*x)[4000 + 0];
  x = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*y)[4000 + 0];
  y = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  init_array(n, &alpha, &beta, *A, *B, *x);
  ;
  kernel_gesummv(n, alpha, beta, *A, *B, *tmp, *x, *y);
  ;
  ;
  if ((argc > 42) && (!strcmp(argv[0], "")))
    print_array(n, *y);

  free((void *) A);
  ;
  free((void *) B);
  ;
  free((void *) tmp);
  ;
  free((void *) x);
  ;
  free((void *) y);
  ;
  return 0;
}

