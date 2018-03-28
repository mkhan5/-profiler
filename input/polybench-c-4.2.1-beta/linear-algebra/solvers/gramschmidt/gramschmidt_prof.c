#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "gramschmidt.h"

/* Header below added by Tulsi */
#include <stdlib.h>

#include<time.h>
extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
extern void polybench_free_data(void *ptr);
extern void polybench_flush_cache();
extern void polybench_prepare_instruments();
static void init_array(int m, int n, double A[1200 + 0][1200 + 0], double R[1200 + 0][1200 + 0], double Q[1200 + 0][1200 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++)
  {
    A[i][j] = ((((double) ((i * j) % m)) / m) * 100) + 10;
    Q[i][j] = 0.0;
  }


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"init_array\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++)
    R[i][j] = 0.0;


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"init_array\",\"Block_Type\":\"For\",\"Block_No\":\"4\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
}

static void print_array(int m, int n, double A[1200 + 0][1200 + 0], double R[1200 + 0][1200 + 0], double Q[1200 + 0][1200 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  fprintf(stderr, "==BEGIN DUMP_ARRAYS==\n");
  fprintf(stderr, "begin dump: %s", "R");
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
  {
    if ((((i * n) + j) % 20) == 0)
      fprintf(stderr, "\n");

    fprintf(stderr, "%0.2lf ", R[i][j]);
  }


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"print_array\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  fprintf(stderr, "\nend   dump: %s\n", "R");
  fprintf(stderr, "begin dump: %s", "Q");
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++)
  {
    if ((((i * n) + j) % 20) == 0)
      fprintf(stderr, "\n");

    fprintf(stderr, "%0.2lf ", Q[i][j]);
  }


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"print_array\",\"Block_Type\":\"For\",\"Block_No\":\"4\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  fprintf(stderr, "\nend   dump: %s\n", "Q");
  fprintf(stderr, "==END   DUMP_ARRAYS==\n");
}

static void kernel_gramschmidt(int m, int n, double A[1200 + 0][1200 + 0], double R[1200 + 0][1200 + 0], double Q[1200 + 0][1200 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  int k;
  double nrm;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (k = 0; k < m; k++)
  {
    nrm = 0.0;
    for (i = 0; i < m; i++)
      nrm += A[i][k] * A[i][k];

    R[k][k] = sqrt(nrm);
    for (i = 0; i < m; i++)
      Q[i][k] = A[i][k] / R[k][k];

    for (j = k + 1; j < m; j++)
    {
      R[k][j] = 0.0;
      for (i = 0; i < m; i++)
        R[k][j] += Q[i][k] * A[i][j];

      for (i = 0; i < m; i++)
        A[i][j] = A[i][j] - (Q[i][k] * R[k][j]);

    }

  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"kernel_gramschmidt\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
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
  int m = 1200;
  int n = 1200;
  double (*A)[1200 + 0][1200 + 0];
  A = (double (*)[1200 + 0][1200 + 0]) polybench_alloc_data((1200 + 0) * (1200 + 0), sizeof(double));
  ;
  double (*R)[1200 + 0][1200 + 0];
  R = (double (*)[1200 + 0][1200 + 0]) polybench_alloc_data((1200 + 0) * (1200 + 0), sizeof(double));
  ;
  double (*Q)[1200 + 0][1200 + 0];
  Q = (double (*)[1200 + 0][1200 + 0]) polybench_alloc_data((1200 + 0) * (1200 + 0), sizeof(double));
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  init_array(m, n, *A, *R, *Q);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"0\",\"Function_Name\":\"init_array\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  kernel_gramschmidt(m, n, *A, *R, *Q);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"4\",\"Function_Name\":\"kernel_gramschmidt\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  ;
  ;
  if ((argc > 42) && (!strcmp(argv[0], "")))
    print_array(m, n, *A, *R, *Q);

  free((void *) A);
  ;
  free((void *) R);
  ;
  free((void *) Q);
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &mend);
  mcpu_time_used = (((double) mend.tv_sec) + (1.0e-9 * mend.tv_nsec)) - (((double) mstart.tv_sec) + (1.0e-9 * mstart.tv_nsec));
  printf("{\"In_Function\":\"\",\"Block_Type\":\"FuncDef\",\"Block_No\":\"\",\"Function_Name\":\"main\",\"Time\":\"%.10f\"}\n", mcpu_time_used);
  return 0;
}

