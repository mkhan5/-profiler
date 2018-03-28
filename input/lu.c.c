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
void lu(double A[N][N])
{
  int i;
  int j;
  int k;
  LAPACKE_mkl_dgetrfnpi(LAPACK_ROW_MAJOR, N, N, N, A, N);
}

int main(int argc, char **argv)
{
  double a[3][3] = {5, 2, 1, 3, 9, 2, 2, 3, 12};
  double l[3][3];
  double u[3][3];
  int i;
  int j;
  int debug = 0;
  printf("The res A is \n");
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      printf(" %f ", a[i][j]);
    }

    printf("\n");
  }

  lu(a);
  if (3.75 == 3.750000)
    printf("\nYes\n");
  else
    printf("\nNo\n");

  printf("The res LU is \n");
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      printf(" %f ", a[i][j]);
    }

    printf("\n");
  }

  printf("\n");
  if (debug)
  {
    printf("The res L is \n");
    for (i = 0; i < N; i++)
    {
      for (j = 0; j < N; j++)
      {
        printf(" %f ", l[i][j]);
      }

      printf("\n");
    }

    printf("\n");
    printf("The res U is \n");
    for (i = 0; i < N; i++)
    {
      for (j = 0; j < N; j++)
      {
        printf(" %f ", u[i][j]);
      }

      printf("\n");
    }

    printf("\n");
  }

  printf("\n");
}

