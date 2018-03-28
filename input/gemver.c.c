
/* Header below added by Tulsi for replaced OpenMP code */
#include <omp.h>
#include "mkl.h"


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
//#define N 3
int N=4;

void gemver( float A[N][N],
           float u1[N],float v1[N],float u2[N],float v2[N],
           float x[N],
           float y[N],
           float w[N],
           float z[N],
           float tmp[N])
{
  int i, j;
  float alpha=1, beta=1;



    alpha = 1.0;
    beta = 0.0;
    cblas_dgemv(CblasRowMajor, CblasNoTrans, N, N, alpha, A, N, x, 1, beta, y, 1);

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      A[i][j] = A[i][j] + u1[i] * v1[j] + u2[i] * v2[j];

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      x[i] = x[i] + beta * A[j][i] * y[j];

  for (i = 0; i < N; i++)
    x[i] = x[i] + z[i];

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      w[i] = w[i] +  alpha * A[i][j] * x[j];

}


int main(int argc, char** argv)
{

  int M = 4;


  //float a[4][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 6, 7, 8};
//  float x[4] = { 2, 1, 3, 5};
  //sol: y = (13, 31, 49)

   float A[4][4];
     float        u1[4],  v1[4],  u2[4],  v2[4],
             x[4],
             y[4],
             w[4],
             z[4],
             tmp[4];



  float res[N];

 // gemver(a, x, res, tmp);
   gemver (A,u1,v1,u2,v2,x,y,w,z,tmp);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));
  int i,j;
  printf("The res x is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",res[i]);
    }

  printf("\n");

}
