#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
/* #define N 3 */
int N=3;

/*
void atax_2( float A[N][N],
             float x[N],
             float y[N],
             float tmp[N])
{
  int i, j;


  for (i = 0; i < N; i++)
    {
      tmp[i] = 0;
      for (j = 0; j < N; j++)
        tmp[i] = tmp[i] + A[i][j] * x[j];
    }
  for (i = 0; i < N; i++)
    {
      y[i] = 0;
      for (j = 0; j < N; j++)
        y[i]=y[i]+A[j][i]*tmp[j];
    }
}
*/

void atax( float A[N][N],
           float x[N],
           float y[N],
           float tmp[N])
{
  int i, j;

  for (i = 0; i < N; i++)
    y[i] = 0;

  for (i = 0; i < N; i++)
    {
      tmp[i] = 0;
      for (j = 0; j < N; j++)
        tmp[i] = tmp[i] + A[i][j] * x[j];
      for (j = 0; j < N; j++)
        y[j] = y[j] + A[i][j] * tmp[i];
    }

}


int main(int argc, char** argv)
{

  int M = 3;
  int n = N;


  float a[3][3] = { 31, 32, 13, 4, 25, 66, 7, 48, 9};
  float x[3] = { 2, 1, 73};
  //sol: x = (1, 2, 3)



  float res[N],tmp[N];

  atax(a, x, res, tmp);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));
  int i,j;
  printf("The res x is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",res[i]);
    }

  printf("\n");

}
