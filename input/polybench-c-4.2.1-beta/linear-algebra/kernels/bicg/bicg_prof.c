#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "bicg.h"

/* Header below added by Tulsi */
#include <stdlib.h>

#include<time.h>
extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
extern void polybench_free_data(void *ptr);
extern void polybench_flush_cache();
extern void polybench_prepare_instruments();
static void init_array(int m, int n, double A[2100 + 0][2100 + 0], double r[2100 + 0], double p[2100 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < m; i++)
    p[i] = ((double) (i % m)) / m;

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"init_array\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
  {
    r[i] = ((double) (i % n)) / n;
    for (j = 0; j < m; j++)
      A[i][j] = ((double) ((i * (j + 1)) % n)) / n;

  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"init_array\",\"Block_Type\":\"For\",\"Block_No\":\"4\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
}

static void print_array(int m, int n, double s[2100 + 0], double q[2100 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  fprintf(stderr, "==BEGIN DUMP_ARRAYS==\n");
  fprintf(stderr, "begin dump: %s", "s");
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < m; i++)
  {
    if ((i % 20) == 0)
      fprintf(stderr, "\n");

    fprintf(stderr, "%0.2lf ", s[i]);
  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"print_array\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  fprintf(stderr, "\nend   dump: %s\n", "s");
  fprintf(stderr, "begin dump: %s", "q");
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
  {
    if ((i % 20) == 0)
      fprintf(stderr, "\n");

    fprintf(stderr, "%0.2lf ", q[i]);
  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"print_array\",\"Block_Type\":\"For\",\"Block_No\":\"4\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  fprintf(stderr, "\nend   dump: %s\n", "q");
  fprintf(stderr, "==END   DUMP_ARRAYS==\n");
}

static void kernel_bicg(int m, int n, double A[2100 + 0][2100 + 0], double s[2100 + 0], double q[2100 + 0], double p[2100 + 0], double r[2100 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
    s[i] = 0;

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"kernel_bicg\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
  {
    q[i] = 0.0;
    for (j = 0; j < n; j++)
    {
      s[j] = s[j] + (r[i] * A[i][j]);
      q[i] = q[i] + (A[i][j] * p[j]);
    }

  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"kernel_bicg\",\"Block_Type\":\"For\",\"Block_No\":\"4\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
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
  int n = 2100;
  int m = 2100;
  double (*A)[2100 + 0][2100 + 0];
  A = (double (*)[2100 + 0][2100 + 0]) polybench_alloc_data((2100 + 0) * (2100 + 0), sizeof(double));
  ;
  double (*s)[2100 + 0];
  s = (double (*)[2100 + 0]) polybench_alloc_data(2100 + 0, sizeof(double));
  ;
  double (*q)[2100 + 0];
  q = (double (*)[2100 + 0]) polybench_alloc_data(2100 + 0, sizeof(double));
  ;
  double (*p)[2100 + 0];
  p = (double (*)[2100 + 0]) polybench_alloc_data(2100 + 0, sizeof(double));
  ;
  double (*r)[2100 + 0];
  r = (double (*)[2100 + 0]) polybench_alloc_data(2100 + 0, sizeof(double));
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  init_array(m, n, *A, *r, *p);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"0\",\"Function_Name\":\"init_array\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  kernel_bicg(m, n, *A, *s, *q, *p, *r);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"4\",\"Function_Name\":\"kernel_bicg\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  ;
  ;
  if ((argc > 42) && (!strcmp(argv[0], "")))
    print_array(m, n, *s, *q);

  free((void *) A);
  ;
  free((void *) s);
  ;
  free((void *) q);
  ;
  free((void *) p);
  ;
  free((void *) r);
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &mend);
  mcpu_time_used = (((double) mend.tv_sec) + (1.0e-9 * mend.tv_nsec)) - (((double) mstart.tv_sec) + (1.0e-9 * mstart.tv_nsec));
  printf("{\"In_Function\":\"\",\"Block_Type\":\"FuncDef\",\"Block_No\":\"\",\"Function_Name\":\"main\",\"Time\":\"%.10f\"}\n", mcpu_time_used);
  return 0;
}

