#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
/* #define N 3 */
int N=3;

void symm(float alpha,
             float beta,
             float A[N][N],
             float B[N][N],
             float C[N][N])
{
  int i, j, k;
  float temp2;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++ )
      {
        temp2 = 0;
        for (k = 0; k < i; k++)
          {
            C[k][j] += alpha*A[i][k]*B[i][j];
            temp2 += A[i][k]*B[k][j];
          }
        C[i][j] = beta * C[i][j] + alpha*B[i][j] * A[i][i] + alpha * temp2;
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

  float a[3][3] = { 1, 0, 0, 2, 5, 0, 3, 6, -3};  // symmetric - so keep in lower tri form
  float b[3][3] = { 1, 0, 1, 3, -1, -2, 0, 2, -1};
  //sol: c = (7, 4, -6)
  //         (17, 7, -14)
  //         (21, -12, -6)


  float res[3][3];

  symm(alpha, beta, a, b, res);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));
  int i,j;
  printf("The res x is \n");
  for( i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++ ){
        printf(" %f ",res[i][j]);
        }
        printf("\n");
    }

  printf("\n");

}
