#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Header below added by Tulsi */
#include <stdlib.h>


/* Header below added by Qahwa for replaced OpenMP code */
/* #include <omp.h> */

int N = 4;
void gesummv(float alf, float bt, float A[N][N], float B[N][N], float x[N], float y[N], float tmp[N])
{
  int i;
  int j;
  for (i = 0; i < N; i++)
  {
    y[i] = 0.0;
  }

  float alpha = 1.0;
  float beta = 0.0;
  cblas_sgemv(CblasRowMajor, CblasNoTrans, N, N, alpha, A, N, x, 1, beta, tmp, 1);
}

int main(int argc, char **argv)
{
  int M = 3;
  int n = N;
  float alf = 1;
  float bt = 1;
  float a[4][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  float b[4][4] = {-1, 0, 3, 2, 3, 0, -1, 4, -5};
  float x[4] = {-1, -3, -2};
  float res[4];
  float tmp[4];
  gesummv(alf, bt, a, b, x, res, tmp);
  int i;
  int j;
  printf("The res x is \n");
  for (i = 0; i < N; i++)
  {
    printf(" %f ", res[i]);
  }

  printf("\n");
}

