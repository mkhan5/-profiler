#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
/* #define N 3 */
int N=4;

void trmm(float alpha,
             float A[N][N],
             float B[N][N])
{
  int i, j, k;

//BLAS parameters
//SIDE   = 'L'
//UPLO   = 'L'
//TRANSA = 'T'
//DIAG   = 'U'
// => Form  B := alpha*A**T*B.
// A is MxM
// B is MxN

  for (i = 0; i < N; i++)
     for (j = 0; j < N; j++)
     {
        for (k = i+1; k < N; k++)
           B[i][j] += A[k][i] * B[k][j];
        B[i][j] = alpha * B[i][j];
     }



}


int main(int argc, char** argv)
{

  int M = 3;
  int n = N;
  float alpha = 1;
  float beta = 0;
 // float a[3][3] = { 3, 2, 5, 2, 5, 4, 5, 4, 7};
 // float b[3][3] = { 1, 2, 3, 2, 4, 5, 3, 5, 8};

  //sol: c = (22, 39, 59)
  //         (24, 44, 63)
  //         (34, 61, 91)

  float a[4][4] = { 1, 0, 0, 0, -9, 1, 0, 0, -12, 13, 1, 0, 7, 12, 18, 1}; // unit, lower triangular
   float b[4][4] = { 1, 4, 3, 2, 5, 4, 11, 41, 81, 17, 1, 5, 24, 13, 10, 7};


  //sol: c = (7, 4, -6)
  //         (17, 7, -14)
  //         (21, -12, -6)


  trmm(alpha, a, b);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));
  int i,j;
  printf("The res x is \n");
  for( i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++ ){
        printf(" %f ",b[i][j]);
        }
        printf("\n");
    }

  printf("\n");

}
