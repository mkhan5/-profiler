#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
/* #define N 3 */
int N=4;

void gesummv(float alf,
             float bt,
             float A[N][N],
             float B[N][N],
           float x[N],
           float y[N],
           float tmp[N])
{
  int i, j;

  for (i = 0; i < N; i++)
    {
      tmp[i] = 0;
      y[i] = 0;
      for (j = 0; j < N; j++)
        {
          tmp[i] = tmp[i] + A[i][j] * x[j] ;
          y[i] = y[i] + B[i][j] * x[j];
        }
      y[i] = alf * tmp[i] + bt * y[i];
    }

}


int main(int argc, char** argv)
{

  int M = 3;
  int n = N;
 float alf = 1;
  float bt = 1;
  float a[4][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
  float b[4][4] = { -1, 0, 3, 2, 3, 0, -1, 4, -5};
  float x[4] = { -1, -3, -2};
  //sol: x = (-18, -42, -50)



  float res[4],tmp[4];

  gesummv(alf, bt, a, b, x, res, tmp);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));
  int i,j;
  printf("The res x is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",res[i]);
    }

  printf("\n");

}