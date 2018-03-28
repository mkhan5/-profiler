
/* Header below added by Tulsi for replaced OpenMP code */
#include <omp.h>
#include "mkl.h"


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

    long long int *mkl_ipiv;
    mkl_ipiv = (long long int *)mkl_malloc( n*sizeof(long long int ), 64 );
    LAPACKE_dgetrf (LAPACK_COL_MAJOR, n, n, A, n, mkl_ipiv );
    LAPACKE_dgetrs (LAPACK_COL_MAJOR, 'T' , n , 1, A, n, mkl_ipiv, b, n);
    cblas_dcopy (n, b, 1, x, 1);
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
