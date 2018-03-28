#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "atax.h"
////#pragma scop
//#pragma endscop

/* Header below added by Tulsi */
#include <stdlib.h>

#include<time.h>
extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
extern void polybench_free_data(void *ptr);
extern void polybench_flush_cache();
extern void polybench_prepare_instruments();
static void init_array(int m, int n, double A[1900 + 0][1900 + 0], double x[1900 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  double fn;
  fn = (double) n;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
    x[i] = 1 + (i / fn);

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"init_array\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
    A[i][j] = ((double) ((i + j) % n)) / (5 * m);


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"init_array\",\"Block_Type\":\"For\",\"Block_No\":\"4\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
}

static void print_array(int n, double y[1900 + 0])
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

static void kernel_atax(int m, int n, double A[1900 + 0][1900 + 0], double x[1900 + 0], double y[1900 + 0], double tmp[1900 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
    y[i] = 0;

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"kernel_atax\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < m; i++)
  {
    tmp[i] = 0.0;
    for (j = 0; j < n; j++)
      tmp[i] = tmp[i] + (A[i][j] * x[j]);

    for (j = 0; j < n; j++)
      y[j] = y[j] + (A[i][j] * tmp[i]);

  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"kernel_atax\",\"Block_Type\":\"For\",\"Block_No\":\"4\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
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
  int m = 1900;
  int n = 1900;
  double (*A)[1900 + 0][1900 + 0];
  A = (double (*)[1900 + 0][1900 + 0]) polybench_alloc_data((1900 + 0) * (1900 + 0), sizeof(double));
  ;
  double (*x)[1900 + 0];
  x = (double (*)[1900 + 0]) polybench_alloc_data(1900 + 0, sizeof(double));
  ;
  double (*y)[1900 + 0];
  y = (double (*)[1900 + 0]) polybench_alloc_data(1900 + 0, sizeof(double));
  ;
  double (*tmp)[1900 + 0];
  tmp = (double (*)[1900 + 0]) polybench_alloc_data(1900 + 0, sizeof(double));
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  init_array(m, n, *A, *x);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"0\",\"Function_Name\":\"init_array\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  kernel_atax(m, n, *A, *x, *y, *tmp);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"4\",\"Function_Name\":\"kernel_atax\",\"Time\":\"%.10f\"}\n", cpu_time_used);
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
  clock_gettime(CLOCK_MONOTONIC_RAW, &mend);
  mcpu_time_used = (((double) mend.tv_sec) + (1.0e-9 * mend.tv_nsec)) - (((double) mstart.tv_sec) + (1.0e-9 * mstart.tv_nsec));
  printf("{\"In_Function\":\"\",\"Block_Type\":\"FuncDef\",\"Block_No\":\"\",\"Function_Name\":\"main\",\"Time\":\"%.10f\"}\n", mcpu_time_used);
  return 0;
}

