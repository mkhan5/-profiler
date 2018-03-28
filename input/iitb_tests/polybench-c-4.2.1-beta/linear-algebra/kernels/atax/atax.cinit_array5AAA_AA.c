#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "atax.h"

/* Header below added by Tulsi */
#include <stdlib.h>

extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
extern void polybench_free_data(void *ptr);
extern void polybench_flush_cache();
extern void polybench_prepare_instruments();
static void init_array(int m, int n, double A[4000 + 0][4000 + 0], double x[4000 + 0])
{
  int i;
  int j;
  double fn;
  fn = (double) n;
  for (i = 0; i < n; i++)
    x[i] = 1 + (i / fn);

  m = 3;
  A[0][0] = 1;
  A[0][1] = 2;
  A[0][2] = 8;
  A[1][0] = 10;
  A[1][1] = 3;
  A[1][2] = 9;
  A[2][0] = 7;
  A[2][1] = 4;
  A[2][2] = 17;
  A[0] = 21;
  A[1] = -13;
  A[2] = -11;
  A[0] = -12;
  A[1] = -3;
  A[2] = 7;
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
    A[i][j] = ((double) ((i + j) % n)) / (5 * m);


  m = 3;
  if (fabs(A[0] + 7) >= 0.000001)
    exit(EXIT_FAILURE);

  if (fabs(A[1] - 5) >= 0.000001)
    exit(EXIT_FAILURE);

  if (fabs(A[2] - 4) >= 0.000001)
    exit(EXIT_FAILURE);

  if (fabs(A[0] - 93) >= 0.000001)
    exit(EXIT_FAILURE);

  if (fabs(A[1] + 72) >= 0.000001)
    exit(EXIT_FAILURE);

  if (fabs(A[2] - 92) >= 0.000001)
    exit(EXIT_FAILURE);

  exit(0);
}

static void print_array(int n, double y[4000 + 0])
{
  int i;
  fprintf(stderr, "==BEGIN DUMP_ARRAYS==\n");
  fprintf(stderr, "begin dump: %s", "y");
  for (i = 0; i < n; i++)
  {
    if ((i % 20) == 0)
      fprintf(stderr, "\n");

    fprintf(stderr, "%0.2lf ", y[i]);
  }

  fprintf(stderr, "\nend   dump: %s\n", "y");
  fprintf(stderr, "==END   DUMP_ARRAYS==\n");
}

static void kernel_atax(int m, int n, double A[4000 + 0][4000 + 0], double x[4000 + 0], double y[4000 + 0], double tmp[4000 + 0])
{
  int i;
  int j;
  for (i = 0; i < n; i++)
    y[i] = 0;

  for (i = 0; i < n; i++)
  {
    tmp[i] = 0.0;
    for (j = 0; j < n; j++)
      tmp[i] = tmp[i] + (A[i][j] * x[j]);

    for (j = 0; j < n; j++)
      y[j] = y[j] + (A[i][j] * tmp[i]);

  }

}

int main(int argc, char **argv)
{
  int m = 4000;
  int n = 4000;
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
  init_array(m, n, *A, *x);
  ;
  kernel_atax(m, n, *A, *x, *y, *tmp);
  ;
  ;
  if ((argc > 42) && (!strcmp(argv[0], "")))
    print_array(n, *y);

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

