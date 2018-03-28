#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
/* #define N 3 */
int N=3;


void cholesky( float A[N][N])
{
  int i, j, k;



  for (i = 0; i < N; i++) {
     //j<i
     for (j = 0; j < i; j++) {
        for (k = 0; k < j; k++) {
           A[i][j] -= A[i][k] * A[j][k];
        }
        A[i][j] /= A[j][j];
     }
     // i==j case
     for (k = 0; k < i; k++) {
        A[i][i] -= A[i][k] * A[i][k];
     }
     A[i][i] = sqrt(A[i][i]);
  }


}


int main(int argc, char** argv)
{


  float a[3][3] = { 2, -1, 0, -1, 2, -1, 0, -1, 2};

  int i,j;

  float res[N],tmp[N];

  printf("The res A is \n");
  for( i = 0; i < N; i++)
    {
        for( j = 0; j < N; j++)
        {
          printf(" %f ",a[i][j]);
        }
        printf("\n");
    }

  cholesky(a);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));

  printf("The res x is \n");
  for( i = 0; i < N; i++)
    {
        for( j = 0; j < N; j++)
        {
          printf(" %f ",a[i][j]);
        }
        printf("\n");
    }

  printf("\n");

}
