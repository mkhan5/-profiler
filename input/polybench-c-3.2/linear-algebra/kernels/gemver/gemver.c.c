#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "gemver.h"

/* Header below added by Tulsi */
#include <stdlib.h>


/* Header below added by Qahwa for replaced OpenMP code */
/* #include <omp.h> */

extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
static void init_array(int n, double *alpha, double *beta, double A[4000 + 0][4000 + 0], double u1[4000 + 0], double v1[4000 + 0], double u2[4000 + 0], double v2[4000 + 0], double w[4000 + 0], double x[4000 + 0], double y[4000 + 0], double z[4000 + 0])
{
  int i;
  int j;
  *alpha = 1;
  *beta = 1;
  for (i = 0; i < n; i++)
  {
    u1[i] = i;
    u2[i] = ((i + 1) / n) / 2.0;
    v1[i] = ((i + 1) / n) / 4.0;
    v2[i] = ((i + 1) / n) / 6.0;
    y[i] = ((i + 1) / n) / 8.0;
    z[i] = ((i + 1) / n) / 9.0;
    x[i] = 0.0;
    w[i] = 0.0;
    for (j = 0; j < n; j++)
      A[i][j] = (((double) i) * j) / n;

  }

}

static void print_array(int n, double w[4000 + 0])
{
  int i;
  for (i = 0; i < n; i++)
  {
    fprintf(stderr, "%0.2lf ", w[i]);
    if ((i % 20) == 0)
      fprintf(stderr, "\n");

  }

}

static void kernel_gemver(int n, double alpha, double beta, double A[4000 + 0][4000 + 0], double u1[4000 + 0], double v1[4000 + 0], double u2[4000 + 0], double v2[4000 + 0], double w[4000 + 0], double x[4000 + 0], double y[4000 + 0], double z[4000 + 0])
{
  int i;
  int j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    A[i][j] = (A[i][j] + (u1[i] * v1[j])) + (u2[i] * v2[j]);


  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    x[i] = x[i] + ((beta * A[j][i]) * y[j]);


  for (i = 0; i < n; i++)
    x[i] = x[i] + z[i];

  for (i = 0; i < n; i++)
  {
    y[i] = 0.0;
  }

  float alpha = 1.0;
  float beta = 0.0;
  cblas_sgemv(CblasRowMajor, CblasNoTrans, n, n, alpha, A, n, x, 1, beta, w, 1);
}

int main(int argc, char **argv)
{
  int n = 4000;
  double alpha;
  double beta;
  double (*A)[4000 + 0][4000 + 0];
  A = (double (*)[4000 + 0][4000 + 0]) polybench_alloc_data((4000 + 0) * (4000 + 0), sizeof(double));
  ;
  double (*u1)[4000 + 0];
  u1 = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*v1)[4000 + 0];
  v1 = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*u2)[4000 + 0];
  u2 = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*v2)[4000 + 0];
  v2 = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*w)[4000 + 0];
  w = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*x)[4000 + 0];
  x = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*y)[4000 + 0];
  y = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  double (*z)[4000 + 0];
  z = (double (*)[4000 + 0]) polybench_alloc_data(4000 + 0, sizeof(double));
  ;
  init_array(n, &alpha, &beta, *A, *u1, *v1, *u2, *v2, *w, *x, *y, *z);
  ;
  kernel_gemver(n, alpha, beta, *A, *u1, *v1, *u2, *v2, *w, *x, *y, *z);
  ;
  ;
  if ((argc > 42) && (!strcmp(argv[0], "")))
    print_array(n, *w);

  free((void *) A);
  ;
  free((void *) u1);
  ;
  free((void *) v1);
  ;
  free((void *) u2);
  ;
  free((void *) v2);
  ;
  free((void *) w);
  ;
  free((void *) x);
  ;
  free((void *) y);
  ;
  free((void *) z);
  ;
  return 0;
}

