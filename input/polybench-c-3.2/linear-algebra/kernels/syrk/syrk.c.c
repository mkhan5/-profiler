#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "syrk.h"

/* Header below added by Tulsi */
#include <stdlib.h>


/* Header below added by Qahwa for replaced OpenMP code */
#include <omp.h>
#include <mkl.h>

extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
static void init_array(int ni, int nj, double *alpha, double *beta, double C[1024 + 0][1024 + 0], double A[1024 + 0][1024 + 0])
{
  int i;
  int j;
  *alpha = 1;
  *beta = 1;
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++)
    A[i][j] = (((double) i) * j) / ni;


  for (i = 0; i < ni; i++)
    for (j = 0; j < ni; j++)
    C[i][j] = (((double) i) * j) / ni;


}

static void print_array(int ni, double C[1024 + 0][1024 + 0])
{
  int i;
  int j;
  for (i = 0; i < ni; i++)
    for (j = 0; j < ni; j++)
  {
    fprintf(stderr, "%0.2lf ", C[i][j]);
    if ((((i * ni) + j) % 20) == 0)
      fprintf(stderr, "\n");

  }


  fprintf(stderr, "\n");
}

static void kernel_syrk(int ni, int nj, double alpha, double beta, double C[1024 + 0][1024 + 0], double A[1024 + 0][1024 + 0])
{
  int i;
  int j;
  int k;
  for (i = 0; i < ni; i++)
    for (j = 0; j < ni; j++)
    C[i][j] *= beta;


  cblas_dsyrk(CblasRowMajor, CblasLower, CblasNoTrans, ni, ni, alpha, A, ni, beta, C, ni);
}

int main(int argc, char **argv)
{
  int ni = 1024;
  int nj = 1024;
  double alpha;
  double beta;
  double (*C)[1024 + 0][1024 + 0];
  C = (double (*)[1024 + 0][1024 + 0]) polybench_alloc_data((1024 + 0) * (1024 + 0), sizeof(double));
  ;
  double (*A)[1024 + 0][1024 + 0];
  A = (double (*)[1024 + 0][1024 + 0]) polybench_alloc_data((1024 + 0) * (1024 + 0), sizeof(double));
  ;
  init_array(ni, nj, &alpha, &beta, *C, *A);
  ;
  kernel_syrk(ni, nj, alpha, beta, *C, *A);
  ;
  ;
  if ((argc > 42) && (!strcmp(argv[0], "")))
    print_array(ni, *C);

  free((void *) C);
  ;
  free((void *) A);
  ;
  return 0;
}

