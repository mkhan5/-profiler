/*
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 7, 2014, 12:01 AM
 * http://stackoverflow.com/questions/22237322/solve-ax-b-a-lower-triangular-matrix-in-c/22237724?noredirect=1#comment33770886_22237724
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

void solve_main( int n, double A[3][3], double b[], double x[])
{
    double w;
    int i,j,k;
    double y[3];

  for (i = 0; i < n; i++) {
    for (j = 0; j <i; j++) {
       w = A[i][j];
       for (k = 0; k < j; k++) {
          w -= A[i][k] * A[k][j];
       }
        A[i][j] = w / A[j][j];
    }
   for (j = i; j < n; j++) {
       w = A[i][j];
       for (k = 0; k < i; k++) {
          w -= A[i][k] * A[k][j];
       }
       A[i][j] = w;
    }
  }

  for (i = 0; i < n; i++) {
     w = b[i];
     for (j = 0; j < i; j++)
        w -= A[i][j] * y[j];
     y[i] = w;
  }

   for (i = n-1; i >=0; i--) {
     w = y[i];
     for (j = i+1; j < n; j++)
        w -= A[i][j] * x[j];
     x[i] = w / A[i][i];
  }
}

/*
 *
 */
int main(int argc, char** argv) {

    int n = 3;
   // double a[4][4] = { 3, 0, 0, 0, -1, 1, 0, 0, 3, -2, -1, 0, 1, -2, 6, 2};
   // double b[4] = { 5, 6, 4, 2};

  //  double a[4][4] = { 4, -1, 2, 3, 0, -2, 7, -4, 0, 0, 6, 5, 0, 0, 0, 3};
  //  double b[4] = { 20, -7, 4, 6};

    // double a[3][3] = { 5, 4, -1, 0, 10, -3, 0, 0, 1};
    // double b[3] = { 0, 11, 3};

   // double a[3][3] = { 2, 1, 1, 0, -8, -2, 0, 0, 1};
   // double b[3] = { 5, -12, 2};
    //sol: x = (2.5, 1.5, 2)

    double a[3][3] = { 1, -2, 3, 5, 8, -1, 2, 1, 1};
    double b[3] = { 9, -5, 3};
    //sol: x = (1, 2, 3)



    double res[3];

    solve_main( n, a, b, res);
    //std::copy( res, res + 3, std::ostream_iterator<double>( std::cout, ","));
     int i,j;
    printf("The res x is \n");
    for( i = 0; i < n; i++) {
        printf(" %f ",res[i]);
    }

    printf("\n");

}
