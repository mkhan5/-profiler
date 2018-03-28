#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Header below added by Tulsi */
#include <stdlib.h>


/* Header below added by Qahwa for replaced OpenMP code */
#include <omp.h>
#include <mkl.h>
int N = 3;
void cholesky(float A[N][N])
{
  int i;
  int j;
  int k;
  LAPACKE_dpotrf(LAPACK_ROW_MAJOR, 'L', N, A, N);
}

int main(int argc, char **argv)
{
  float a[3][3] = {2, -1, 0, -1, 2, -1, 0, -1, 2};
  int i;
  int j;
  float res[N];
  float tmp[N];
  printf("The res A is \n");
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      printf(" %f ", a[i][j]);
    }

    printf("\n");
  }

  cholesky(a);
  printf("The res x is \n");
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      printf(" %f ", a[i][j]);
    }

    printf("\n");
  }

  printf("\n");
}

