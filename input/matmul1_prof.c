#include <stdio.h>
#include <stdlib.h>

/* Header below added by Tulsi */
#include <stdlib.h>

#include<time.h>
int N = 2000;
static void simple_sgemm(int n, float alpha, float *A, float *B, float beta, float *C)
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  int i;
  int j;
  int k;
  float prod;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n; ++j)
    {
      prod = 0;
      for (k = 0; k < n; ++k)
      {
        prod += B[(k * n) + i] * A[(j * n) + k];
      }

      C[(j * n) + i] = (alpha * prod) + (beta * C[(j * n) + i]);
    }

  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("For %.10f\n", cpu_time_used);
}

int main(int argc, char **argv)
{
  struct timespec start;
  struct timespec end;
  double cpu_time_used;
  float *h_A;
  float *h_B;
  float *h_C;
  float *h_C_ref;
  float alpha = 1.0f;
  float beta = 0.0f;
  int n2 = N * N;
  int i;
  printf("simpleCUBLAS test running..\n");
  h_A = (float *) malloc(n2 * (sizeof(h_A[0])));
  h_B = (float *) malloc(n2 * (sizeof(h_B[0])));
  if (h_B == 0)
  {
    fprintf(stderr, "!!!! host memory allocation error (B)\n");
    return 1;
  }

  h_C = (float *) malloc(n2 * (sizeof(h_C[0])));
  if (h_C == 0)
  {
    fprintf(stderr, "!!!! host memory allocation error (C)\n");
    return 1;
  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  for (i = 0; i < n2; i++)
  {
    h_A[i] = rand() / ((float) 32767);
    h_B[i] = rand() / ((float) 32767);
    h_C[i] = rand() / ((float) 32767);
  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("For %.10f\n", cpu_time_used);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  simple_sgemm(N, alpha, h_A, h_B, beta, h_C);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  cpu_time_used = (((double) end.tv_sec) + (1.0e-9 * end.tv_nsec)) - (((double) start.tv_sec) + (1.0e-9 * start.tv_nsec));
  printf("FuncCall %.10f\n", cpu_time_used);
  free(h_A);
  free(h_B);
  free(h_C);
}

