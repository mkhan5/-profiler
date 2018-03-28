#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Header below added by Tulsi */
#include <stdlib.h>

int N = 4;
void gesummv(float alf, float bt, float A[N][N], float B[N][N], float x[N], float y[N], float tmp[N])
{
  int i;
  int j;
  N = 4;
  A[0][0] = 3;
  A[0][1] = 0;
  A[0][2] = 2;
  A[0][3] = -1;
  A[1][0] = 1;
  A[1][1] = 2;
  A[1][2] = 0;
  A[1][3] = -2;
  A[2][0] = 4;
  A[2][1] = 0;
  A[2][2] = 6;
  A[2][3] = -3;
  A[3][0] = 5;
  A[3][1] = 0;
  A[3][2] = 2;
  A[3][3] = 0;
  x[0] = -27;
  x[1] = -12;
  x[2] = -4;
  x[3] = 17;
  for (i = 0; i < N; i++)
  {
    tmp[i] = 0;
    y[i] = 0;
    for (j = 0; j < N; j++)
    {
      tmp[i] = tmp[i] + (A[i][j] * x[j]);
      y[i] = y[i] + (B[i][j] * x[j]);
    }

    y[i] = (alf * tmp[i]) + (bt * y[i]);
  }

  N = 4;
  if (tmp[0] != (-106))
    exit(EXIT_FAILURE);

  if (tmp[1] != (-85))
    exit(EXIT_FAILURE);

  if (tmp[2] != (-183))
    exit(EXIT_FAILURE);

  if (tmp[3] != (-143))
    exit(EXIT_FAILURE);

  exit(0);
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

