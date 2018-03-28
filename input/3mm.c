#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
//#define N 3
int N=3;

void mm( double A[N][N],
            double B[N][N],
            double C[N][N],
            double D[N][N],
            double E[N][N],
            double tmp1[N][N],
            double tmp2[N][N]
           )
{
  int i, j,k;

   /* tmp1 := A*B */
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      {
	tmp1[i][j] = (0.0);
	for (k = 0; k < N; ++k)
	  tmp1[i][j] += A[i][k] * B[k][j];
      }
  /* tmp2 := C*D */
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      {
	tmp2[i][j] = (0.0);
	for (k = 0; k < N; ++k)
	  tmp2[i][j] += C[i][k] * D[k][j];
      }
  /* E := tmp1*tmp2 */
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      {
	E[i][j] = (0.0);
	for (k = 0; k < N; ++k)
	  E[i][j] += tmp1[i][k] * tmp2[k][j];
      }

}



int main(int argc, char** argv)
{

  int M = 3;


    double a[3][3] = { 1, 2, 5, 9, 23, -7, 6, 1, -3};
    double b[3][3] = {1, 5, -1, -2, 1, 21, -30, -11, -15};
    double c[3][3] = {1, 5, -1, -2, 1, 21, -30, -11, -15};
    double d[3][3] = { 1, 2, 5, 9, 23, -7, 6, 1, -3};

//    double a[3][3] = { 24, -22, -4, -11, 12, 10, -23, -18, -12};
//    double b[3][3] = { 20, -25, -1, -2, -3, 14, -24, -9, -19};
//    double c[3][3] = {-17, -16, 19, 8, 5, 4, 17, -13, 22};
//    double d[3][3] = {-5, -8, -6, 1, -15, 23, 3, -21, 11};

  double tmp1[3][3];
  double tmp2[3][3];
  double e[3][3];
  //sol: y = (13, 31, 49)
  double alpha = 1;
  double beta = 0;

  mm(a, b, c, d, e, tmp1, tmp2);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));
  int i,j;
  printf("The res E = tmp1.tmp2 is \n");
  for( i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
      {
        printf(" %f ",e[i][j]);
       }
       printf("\n");
    }

  printf("\n");

}
