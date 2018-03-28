
/* Header below added by Qahwa for replaced OpenMP code */
#include <omp.h>
#include <mkl.h>


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


void func(void)
{
    double *tau;
    tau = (double *)mkl_malloc( N*sizeof( double ), 64 );
    LAPACKE_dgeqrf (LAPACK_ROW_MAJOR, N, N, A, N, tau);
    cblas_dcopy (N, A, 1, R, 1);
    LAPACKE_dorgqr(LAPACK_ROW_MAJOR, N, N, N, A, N, tau);
    cblas_dcopy (N, A, 1, Q, 1);
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
