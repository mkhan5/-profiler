#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
int N = 4;

void syrk( float A[N][N],
           float C[N][N],
           float alpha,
           float beta)
{
  int i, j, k;

  /*  C := alpha*A*A' + beta*C */
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      C[i][j] *= beta;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      for (k = 0; k < N; k++)
        C[i][j] += alpha * A[i][k] * A[j][k];

}


int main(int argc, char** argv)
{

  float alpha = 1;
  float beta = 1;
  float a[4][4] = { 2, 1, 1, -5, -3, 0, 1, 1, -1};
  float c[4][4] = { 1, 0, 0, 2, 5, 0, 3, 6, -5};  // symmetric - so keep in lower tri form
  //sol: x = (-89, 19, 177)


  float res[N],tmp[N];

  syrk(a, c, alpha, beta);
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
