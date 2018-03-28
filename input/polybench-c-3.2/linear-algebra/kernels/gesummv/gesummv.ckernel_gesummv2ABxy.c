#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "gesummv.h"

/* Header below added by Tulsi */
#include <stdlib.h>

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
  n = 3;
  A[0][0] = -1;
  A[0][1] = 3;
  A[0][2] = -3;
  A[1][0] = 0;
  A[1][1] = -6;
  A[1][2] = 5;
  A[2][0] = -5;
  A[2][1] = -3;
  A[2][2] = 1;
  B[0][0] = 1;
  B[0][1] = -4;
  B[0][2] = 2;
  B[1][0] = -1;
  B[1][1] = 1;
  B[1][2] = -1;
  B[2][0] = 3;
  B[2][1] = -6;
  B[2][2] = 4;
  x[0] = -5;
  x[1] = -3;
  x[2] = -6;
  for (i = 0; i < n; i++)
  {
    tmp[i] = 0;
    y[i] = 0;
    for (j = 0; j < n; j++)
    {
      tmp[i] = (A[i][j] * x[j]) + tmp[i];
      y[i] = (B[i][j] * x[j]) + y[i];
    }

    y[i] = (alpha * tmp[i]) + (beta * y[i]);
  }

  n = 3;
  if (y[0] != 9)
    exit(EXIT_FAILURE);

  if (y[1] != (-4))
    exit(EXIT_FAILURE);

  if (y[2] != 7)
    exit(EXIT_FAILURE);

  exit(0);
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

