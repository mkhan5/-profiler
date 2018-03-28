#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


//#define N 3
int N=3;

void mvt( double A[N][N],
           double x1[N],
           double x2[N],
           double y_1[N],
           double y_2[N])
{
  int i, j;

    for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      x1[i] = x1[i] + A[i][j] * y_1[j];
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      x2[i] = x2[i] + A[j][i] * y_2[j];

}


int main(int argc, char** argv)
{

  int M = 4;
  int i,j;

  //double a[4][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 6, 7, 8};
  //double x[4] = { 2, 1, 3, 5};
  double a[3][3] = { 1, -2, 3, 4, 6, 6, -17, -11, 8};
  double x1[3] = { -5, -9, 6};
  double x2[3] = { -2, 3, 21};
  double y1[3] = { -1, -4, 23};
  double y2[3] = { 7, -8, -19};

printf("The x1 is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",x1[i]);
    }

  printf("\n");
  printf("The x2 is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",x2[i]);
    }

  printf("\n");

    mvt(a, x1, x2, y1, y2);
  //std::copy( res, res + 3, std::ostream_iterator<double>( std::cout, ","));

  printf("The res x1 is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",x1[i]);
    }

  printf("\n");
  printf("The res x2 is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",x2[i]);
    }

  printf("\n");

}
