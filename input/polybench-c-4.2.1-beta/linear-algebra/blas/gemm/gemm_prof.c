#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <polybench.h>
#include "gemm.h"

/* Header below added by Tulsi */
#include <stdlib.h>

#include<time.h>
extern void *polybench_alloc_data(unsigned long long int n, int elt_size);
extern void polybench_free_data(void *ptr);
extern void polybench_flush_cache();
extern void polybench_prepare_instruments();
static void init_array(int ni, int nj, int nk, double *alpha, double *beta, double C[1200 + 0][1200 + 0], double A[1200 + 0][1200 + 0], double B[1200 + 0][1200 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  *alpha = 1;
  *beta = 0;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++)
    C[i][j] = ((double) (((i * j) + 1) % ni)) / ni;


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"init_array\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < ni; i++)
    for (j = 0; j < nk; j++)
    A[i][j] = ((double) ((i * (j + 1)) % nk)) / nk;


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"init_array\",\"Block_Type\":\"For\",\"Block_No\":\"4\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < nk; i++)
    for (j = 0; j < nj; j++)
    B[i][j] = ((double) ((i * (j + 2)) % nj)) / nj;


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"init_array\",\"Block_Type\":\"For\",\"Block_No\":\"8\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
}

static void print_array(int ni, int nj, double C[1200 + 0][1200 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  fprintf(stderr, "==BEGIN DUMP_ARRAYS==\n");
  fprintf(stderr, "begin dump: %s", "C");
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++)
  {
    if ((((i * ni) + j) % 20) == 0)
      fprintf(stderr, "\n");

    fprintf(stderr, "%0.2lf ", C[i][j]);
  }


  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"print_array\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  fprintf(stderr, "\nend   dump: %s\n", "C");
  fprintf(stderr, "==END   DUMP_ARRAYS==\n");
}

static void kernel_gemm(int ni, int nj, int nk, double alpha, double beta, double C[1200 + 0][1200 + 0], double A[1200 + 0][1200 + 0], double B[1200 + 0][1200 + 0])
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  int k;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < ni; i++)
  {
    for (j = 0; j < ni; j++)
      C[i][j] *= beta;

    for (k = 0; k < ni; k++)
    {
      for (j = 0; j < ni; j++)
        C[i][j] += (alpha * A[i][k]) * B[k][j];

    }

  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"kernel_gemm\",\"Block_Type\":\"For\",\"Block_No\":\"0\",\"Function_Name\":\"\",\"Time\":\"%.10f\"}\n", cpu_time_used);
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
  int ni = 1200;
  int nj = 1200;
  int nk = 1200;
  double alpha;
  double beta;
  double (*C)[1200 + 0][1200 + 0];
  C = (double (*)[1200 + 0][1200 + 0]) polybench_alloc_data((1200 + 0) * (1200 + 0), sizeof(double));
  ;
  double (*A)[1200 + 0][1200 + 0];
  A = (double (*)[1200 + 0][1200 + 0]) polybench_alloc_data((1200 + 0) * (1200 + 0), sizeof(double));
  ;
  double (*B)[1200 + 0][1200 + 0];
  B = (double (*)[1200 + 0][1200 + 0]) polybench_alloc_data((1200 + 0) * (1200 + 0), sizeof(double));
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  init_array(ni, nj, nk, &alpha, &beta, *C, *A, *B);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"0\",\"Function_Name\":\"init_array\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  kernel_gemm(ni, nj, nk, alpha, beta, *C, *A, *B);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("{\"In_Function\":\"main\",\"Block_Type\":\"FuncCall\",\"Block_No\":\"4\",\"Function_Name\":\"kernel_gemm\",\"Time\":\"%.10f\"}\n", cpu_time_used);
  ;
  ;
  if ((argc > 42) && (!strcmp(argv[0], "")))
    print_array(ni, nj, *C);

  free((void *) C);
  ;
  free((void *) A);
  ;
  free((void *) B);
  ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &mend);
  mcpu_time_used = (((double) mend.tv_sec) + (1.0e-9 * mend.tv_nsec)) - (((double) mstart.tv_sec) + (1.0e-9 * mstart.tv_nsec));
  printf("{\"In_Function\":\"\",\"Block_Type\":\"FuncDef\",\"Block_No\":\"\",\"Function_Name\":\"main\",\"Time\":\"%.10f\"}\n", mcpu_time_used);
  return 0;
}

