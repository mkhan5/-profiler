#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
int N = 4;

void syr2k( float A[N][N],
           float B[N][N],
           float C[N][N],
           float alpha,
           float beta)
{
  int i, j, k;

  /*  C := alpha*A*A' + beta*C */
  for (i = 0; i < N; i++) {
    for (j = 0; j <= i; j++)
      C[i][j] *= beta;

    for (k = 0; k < N; k++)
      for (j = 0; j <= i; j++)
	{
	  C[i][j] += A[j][k]*alpha*B[i][k] + B[j][k]*alpha*A[i][k];
	}
  }
}


int main(int argc, char** argv)
{

  float alpha = 1;
  float beta = 1;


  float a[4][4] = { -1, -3, -7, 8, 9, 13, -5, -6, -7, 12, 17, 19, 11, -7, 22, -17};
  float b[4][4] = { 1, 2, -1, 0, 0, 5, 3, 0, -2, 0, 0, 4, 0, 6, -4, -3};
  float c[4][4] = { -11, 0, 0, 0, 13, -19, 0, 0, -17, -7, 9, 0, 7, -3, -13, 11};  //symmetric matrix (lower triangular form)
  //sol: x = (-89, 19, 177)


  float res[N],tmp[N];

  syr2k(a, b, c, alpha, beta);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));
  int i,j;
  printf("The res C is \n");
  for( i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++ ){
        printf(" %f ",c[i][j]);
        }
        printf("\n");
    }

  printf("\n");

}
