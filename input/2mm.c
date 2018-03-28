#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
//#define N 3
int N=3;

void mm2( double A[N][N],
            double B[N][N],
            double C[N][N],
            double D[N][N],
            double tmp[N][N],
            double alpha,
            double beta
           )
{
  int i, j,k;

  /* D := alpha*A*B*C + beta*D */
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      {
	    tmp[i][j] = 0.0;
	    for (k = 0; k < N; ++k)
	    tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      {
	    D[i][j] *= beta;
	    for (k = 0; k < N; ++k)
	    D[i][j] += tmp[i][k] * C[k][j];
      }

}


int main(int argc, char** argv)
{

  int M = 3;


  double a[3][3] = { 1, 2, 5, 9, 23, -7, 6, 1, -3};
  double b[3][3] = { 17, 2, -1, -12, -19, -22, -1, 3, 9};
  double c[3][3] = {1, 5, -1, -2, 1, 21, -30, -11, -15};
  double tmp[3][3];
  double d[3][3];
  //sol: y = (13, 31, 49)
  double alpha = 1;
  double beta = 0;

  mm2(a, b, c, d, tmp, alpha, beta);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));
  int i,j;
  printf("The res x is \n");
  for( i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
      {
        printf(" %f ",d[i][j]);
       }
       printf("\n");
    }

  printf("\n");

}
