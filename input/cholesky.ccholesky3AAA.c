#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Header below added by Tulsi */
#include <stdlib.h>

int N = 3;
void cholesky(float A[N][N])
{
  int i;
  int j;
  int k;
  N = 3;
  A[0][0] = 25;
  A[0][1] = 15;
  A[0][2] = -5;
  A[1][0] = 15;
  A[1][1] = 18;
  A[1][2] = 0;
  A[2][0] = -5;
  A[2][1] = 0;
  A[2][2] = 11;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < i; j++)
    {
      for (k = 0; k < j; k++)
      {
        A[i][j] -= A[i][k] * A[j][k];
      }

      A[i][j] /= A[j][j];
    }

    for (k = 0; k < i; k++)
    {
      A[i][i] -= A[i][k] * A[i][k];
    }

    A[i][i] = sqrt(A[i][i]);
  }

  N = 3;
  if (A[0][0] != 5)
    exit(EXIT_FAILURE);

  if (A[1][0] != 3)
    exit(EXIT_FAILURE);

  if (A[1][1] != 3)
    exit(EXIT_FAILURE);

  if (A[2][0] != (-1))
    exit(EXIT_FAILURE);

  if (A[2][1] != 1)
    exit(EXIT_FAILURE);

  if (A[2][2] != 3)
    exit(EXIT_FAILURE);

  exit(0);
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

