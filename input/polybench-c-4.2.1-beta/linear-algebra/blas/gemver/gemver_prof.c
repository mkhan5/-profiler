#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "gemver.h"

/* Header below added by Tulsi */
#include <stdlib.h>

#include<time.h>
extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
extern void polybench_free_data(void *ptr);
extern void polybench_flush_cache();
extern void polybench_prepare_instruments();
static void init_array(int n, double *alpha, double *beta, double A[2000 + 0][2000 + 0], double u1[2000 + 0], double v1[2000 + 0], double u2[2000 + 0], double v2[2000 + 0], double w[2000 + 0], double x[2000 + 0], double y[2000 + 0], double z[2000 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  *alpha = 1;
  *beta = 1;
  double fn = (double) n;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
  {
    u1[i] = i;
    u2[i] = ((i + 1) / fn) / 2.0;
    v1[i] = ((i + 1) / fn) / 4.0;
    v2[i] = ((i + 1) / fn) / 6.0;
    y[i] = ((i + 1) / fn) / 8.0;
    z[i] = ((i + 1) / fn) / 9.0;
    x[i] = 0.0;
    w[i] = 0.0;
    for (j = 0; j < n; j++)
      A[i][j] = ((double) ((i * j) % n)) / n;

  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"init_array\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
}

static void print_array(int n, double w[2000 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  fprintf(stderr, "==BEGIN DUMP_ARRAYS==\n");
  fprintf(stderr, "begin dump: %s", "w");
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
  {
    if ((i % 20) == 0)
      fprintf(stderr, "\n");

    fprintf(stderr, "%0.2lf ", w[i]);
  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"print_array\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  fprintf(stderr, "\nend   dump: %s\n", "w");
  fprintf(stderr, "==END   DUMP_ARRAYS==\n");
}

static void kernel_gemver(int n, double alpha, double beta, double A[2000 + 0][2000 + 0], double u1[2000 + 0], double v1[2000 + 0], double u2[2000 + 0], double v2[2000 + 0], double w[2000 + 0], double x[2000 + 0], double y[2000 + 0], double z[2000 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    A[i][j] = (A[i][j] + (u1[i] * v1[j])) + (u2[i] * v2[j]);


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"kernel_gemver\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    x[i] = x[i] + ((beta * A[j][i]) * y[j]);


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"kernel_gemver\",\"Block_Type\":\"For\",\"Block_No\":\"4\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
    x[i] = x[i] + z[i];

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"kernel_gemver\",\"Block_Type\":\"For\",\"Block_No\":\"8\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    w[i] = w[i] + ((alpha * A[i][j]) * x[j]);


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"kernel_gemver\",\"Block_Type\":\"For\",\"Block_No\":\"12\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
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
  int n = 2000;
  double alpha;
  double beta;
  double (*A)[2000 + 0][2000 + 0];
  A = (double (*)[2000 + 0][2000 + 0]) polybench_alloc_data((2000 + 0) * (2000 + 0), sizeof(double));
  ;
  double (*u1)[2000 + 0];
  u1 = (double (*)[2000 + 0]) polybench_alloc_data(2000 + 0, sizeof(double));
  ;
  double (*v1)[2000 + 0];
  v1 = (double (*)[2000 + 0]) polybench_alloc_data(2000 + 0, sizeof(double));
  ;
  double (*u2)[2000 + 0];
  u2 = (double (*)[2000 + 0]) polybench_alloc_data(2000 + 0, sizeof(double));
  ;
  double (*v2)[2000 + 0];
  v2 = (double (*)[2000 + 0]) polybench_alloc_data(2000 + 0, sizeof(double));
  ;
  double (*w)[2000 + 0];
  w = (double (*)[2000 + 0]) polybench_alloc_data(2000 + 0, sizeof(double));
  ;
  double (*x)[2000 + 0];
  x = (double (*)[2000 + 0]) polybench_alloc_data(2000 + 0, sizeof(double));
  ;
  double (*y)[2000 + 0];
  y = (double (*)[2000 + 0]) polybench_alloc_data(2000 + 0, sizeof(double));
  ;
  double (*z)[2000 + 0];
  z = (double (*)[2000 + 0]) polybench_alloc_data(2000 + 0, sizeof(double));
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  init_array(n, &alpha, &beta, *A, *u1, *v1, *u2, *v2, *w, *x, *y, *z);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"0\",\"Function_Name\":\"init_array\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  kernel_gemver(n, alpha, beta, *A, *u1, *v1, *u2, *v2, *w, *x, *y, *z);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"4\",\"Function_Name\":\"kernel_gemver\",\"Time\":\"%.10f\"}\n", cpu_time_used);
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
  clock_gettime(CLOCK_MONOTONIC_RAW, &mend);
  mcpu_time_used = (((double) mend.tv_sec) + (1.0e-9 * mend.tv_nsec)) - (((double) mstart.tv_sec) + (1.0e-9 * mstart.tv_nsec));
  printf("{\"In_Function\":\"\",\"Block_Type\":\"FuncDef\",\"Block_No\":\"\",\"Function_Name\":\"main\",\"Time\":\"%.10f\"}\n", mcpu_time_used);
  return 0;
}

