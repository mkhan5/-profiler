#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
//#define N 3
int N=4;

void gemv( float A[N][N],
           float x[N],
           float y[N],
           float tmp[N])
{
  int i, j;


  for (i = 0; i < N; i++)
    {
      y[i] = 0;
      for (j = 0; j < N; j++)
        y[i] = y[i] + A[i][j] * x[j];

    }

}


int main(int argc, char** argv)
{

  int M = 4;


  float a[4][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 6, 7, 8};
  float x[4] = { 2, 1, 3, 5};
  //sol: y = (13, 31, 49)



  float res[N],tmp[N];

  gemv(a, x, res, tmp);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));
  int i,j;
  printf("The res x is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",res[i]);
    }

  printf("\n");

}
