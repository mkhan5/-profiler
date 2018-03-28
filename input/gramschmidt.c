#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
/* #define N 3 */
int N=3;


void qr( float A[N][N],float R[N][N],float Q[N][N])
{
  int i, j, k;

  double nrm;


  for (k = 0; k < N; k++)
    {
      nrm = 0.0;
      for (i = 0; i < N; i++)
        nrm += A[i][k] * A[i][k];
      R[k][k] = sqrt(nrm);
      for (i = 0; i < N; i++)
        Q[i][k] = A[i][k] / R[k][k];
      for (j = k + 1; j < N; j++)
        {
          R[k][j] = 0.0;
          for (i = 0; i < N; i++)
            R[k][j] += Q[i][k] * A[i][j];
          for (i = 0; i < N; i++)
            A[i][j] = A[i][j] - Q[i][k] * R[k][j];
        }
    }

}


int main(int argc, char** argv)
{


  float a[3][3] = { 2, -1, 0, -1, 2, -1, 0, -1, 2};

  int i,j;

  float q[3][3],r[3][3];

  printf("The res A is \n");
  for( i = 0; i < N; i++)
    {
      for( j = 0; j < N; j++)
        {
          printf(" %f ",a[i][j]);
        }
      printf("\n");
    }

  qr(a,r,q);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));

  printf("The res Q is \n");
  for( i = 0; i < N; i++)
    {
      for( j = 0; j < N; j++)
        {
          printf(" %f ",q[i][j]);
        }
      printf("\n");
    }

  printf("\n");

  printf("The res R is \n");
  for( i = 0; i < N; i++)
    {
      for( j = 0; j < N; j++)
        {
          printf(" %f ",r[i][j]);
        }
      printf("\n");
    }

  printf("\n");

}
