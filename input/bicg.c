#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


//#define N 3
int N=3;

void bicg( double A[N][N],
           double s[N],
           double q[N],
           double p[N],
           double r[N])
{
  int i, j;

  for (i = 0; i < N; i++)
    s[i] = 0;

  for (i = 0; i < N; i++)
    {
      q[i] = 0.0;
      for (j = 0; j < N; j++)
	{
	  s[j] = s[j] + r[i] * A[i][j];
	  q[i] = q[i] + A[i][j] * p[j];
	}
    }

}


int main(int argc, char** argv)
{

  int M = 4;


  //double a[4][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 6, 7, 8};
  //double x[4] = { 2, 1, 3, 5};
  double a[3][3] = { 1, 2, 3, 4, 5, 9, 7, 4, 17};
  double p[3] = { 2, -3, 1};
  double r[3] = { -2, -13, 17};

  double resS[3],resQ[3];

  bicg(a, resS, resQ, p, r);
  //std::copy( res, res + 3, std::ostream_iterator<double>( std::cout, ","));
  int i,j;
  printf("The res S is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",resS[i]);
    }

  printf("\n");
  printf("The res Q is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",resQ[i]);
    }

  printf("\n");

}
