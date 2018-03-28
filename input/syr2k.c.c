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
void syr2k(float A[N][N], float B[N][N], float C[N][N], float alpha, float beta)
{
  int i;
  int j;
  int k;
  cblas_dsyr2k(CblasRowMajor, CblasLower, CblasNoTrans, N, N, alpha, A, N, B, N, beta, C, N);
}

int main(int argc, char **argv)
{
  float alpha = 1;
  float beta = 1;
  float a[4][4] = {-1, -3, -7, 8, 9, 13, -5, -6, -7, 12, 17, 19, 11, -7, 22, -17};
  float b[4][4] = {1, 2, -1, 0, 0, 5, 3, 0, -2, 0, 0, 4, 0, 6, -4, -3};
  float c[4][4] = {-11, 0, 0, 0, 13, -19, 0, 0, -17, -7, 9, 0, 7, -3, -13, 11};
  float res[N];
  float tmp[N];
  syr2k(a, b, c, alpha, beta);
  int i;
  int j;
  printf("The res C is \n");
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      printf(" %f ", c[i][j]);
    }

    printf("\n");
  }

  printf("\n");
}

