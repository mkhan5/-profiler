#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "gesummv.h"

/* Header below added by Tulsi */
#include <stdlib.h>

#include<time.h>
extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
extern void polybench_free_data(void *ptr);
extern void polybench_flush_cache();
extern void polybench_prepare_instruments();
static void init_array(int n, double *alpha, double *beta, double A[1300 + 0][1300 + 0], double B[1300 + 0][1300 + 0], double x[1300 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  *alpha = 1;
  *beta = 1;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
  {
    x[i] = ((double) (i % n)) / n;
    for (j = 0; j < n; j++)
    {
      A[i][j] = ((double) (((i * j) + 1) % n)) / n;
      B[i][j] = ((double) (((i * j) + 2) % n)) / n;
    }

  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"init_array\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
}

static void print_array(int n, double y[1300 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  fprintf(stderr, "==BEGIN DUMP_ARRAYS==\n");
  fprintf(stderr, "begin dump: %s", "y");
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
  {
    if ((i % 20) == 0)
      fprintf(stderr, "\n");

    fprintf(stderr, "%0.2lf ", y[i]);
  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"print_array\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  fprintf(stderr, "\nend   dump: %s\n", "y");
  fprintf(stderr, "==END   DUMP_ARRAYS==\n");
}

static void kernel_gesummv(int n, double alpha, double beta, double A[1300 + 0][1300 + 0], double B[1300 + 0][1300 + 0], double tmp[1300 + 0], double x[1300 + 0], double y[1300 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
  {
    tmp[i] = 0.0;
    y[i] = 0.0;
    for (j = 0; j < n; j++)
    {
      tmp[i] = (A[i][j] * x[j]) + tmp[i];
      y[i] = (B[i][j] * x[j]) + y[i];
    }

    y[i] = (alpha * tmp[i]) + (beta * y[i]);
  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"kernel_gesummv\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
}

int main(int argc, char **argv)
{
  struct timespec mstart;
  struct timespec mend;
  double mcpu_time_used;
  clock_gettime(CLOCK_MONOTONIC_RAW, &mstart);
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int n = 1300;
  double alpha;
  double beta;
  double (*A)[1300 + 0][1300 + 0];
  A = (double (*)[1300 + 0][1300 + 0]) polybench_alloc_data((1300 + 0) * (1300 + 0), sizeof(double));
  ;
  double (*B)[1300 + 0][1300 + 0];
  B = (double (*)[1300 + 0][1300 + 0]) polybench_alloc_data((1300 + 0) * (1300 + 0), sizeof(double));
  ;
  double (*tmp)[1300 + 0];
  tmp = (double (*)[1300 + 0]) polybench_alloc_data(1300 + 0, sizeof(double));
  ;
  double (*x)[1300 + 0];
  x = (double (*)[1300 + 0]) polybench_alloc_data(1300 + 0, sizeof(double));
  ;
  double (*y)[1300 + 0];
  y = (double (*)[1300 + 0]) polybench_alloc_data(1300 + 0, sizeof(double));
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  init_array(n, &alpha, &beta, *A, *B, *x);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"0\",\"Function_Name\":\"init_array\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  kernel_gesummv(n, alpha, beta, *A, *B, *tmp, *x, *y);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"4\",\"Function_Name\":\"kernel_gesummv\",\"Time\":\"%.10f\"}\n", cpu_time_used);
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
  clock_gettime(CLOCK_MONOTONIC_RAW, &mend);
  mcpu_time_used = (((double) mend.tv_sec) + (1.0e-9 * mend.tv_nsec)) - (((double) mstart.tv_sec) + (1.0e-9 * mstart.tv_nsec));
  printf("{\"In_Function\":\"\",\"Block_Type\":\"FuncDef\",\"Block_No\":\"\",\"Function_Name\":\"main\",\"Time\":\"%.10f\"}\n", mcpu_time_used);
  return 0;
}

