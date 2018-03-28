#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Header below added by Tulsi */
#include <stdlib.h>


/* Header below added by Qahwa for replaced OpenMP code */
#include <omp.h>
#include <mkl.h>

int N = 4;
void trmm(float alpha, float A[N][N], float B[N][N])
{
  int i;
  int j;
  int k;
  cblas_dtrmm(CblasRowMajor, CblasLeft, CblasLower, CblasTrans, CblasUnit, N, N, alpha, A, N, B, N);
}

int main(int argc, char **argv)
{
  int M = 3;
  int n = N;
  float alpha = 1;
  float beta = 0;
  float a[4][4] = {1, 0, 0, 0, -9, 1, 0, 0, -12, 13, 1, 0, 7, 12, 18, 1};
  float b[4][4] = {1, 4, 3, 2, 5, 4, 11, 41, 81, 17, 1, 5, 24, 13, 10, 7};
  trmm(alpha, a, b);
  int i;
  int j;
  printf("The res x is \n");
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      printf(" %f ", b[i][j]);
    }

    printf("\n");
  }

  printf("\n");
}

