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

/**
 * solve linear equation system by forward
 * substitution on lower triangular matrix
 * @param n matrix rank (dimension of solution space)
 * @param a lower triangular matrix
 * @param b right side
 * @param x solution
 * http://k...content-available-to-author-only...u.tr/~pehlivan/numerical_analysis/chap02/BackSubstitution.pdf
 */
void solve_main( int n, float a[3][3], float b[], float x[]) {
  float s;
   int i,j;
  for( i = 0; i < n; i++) {
        s = 0;
        for( j = 0; j < i; j++) {
            s = s + a[ i][ j] * x[ j];
        }
        x[ i] = ( b[ i] - s) / a[ i][ i];
   }
}

/*
 *
 */
int main(int argc, char** argv) {

    int n = 3;
   // float a[4][4] = { 3, 0, 0, 0, -1, 1, 0, 0, 3, -2, -1, 0, 1, -2, 6, 2};
   // float b[4] = { 5, 6, 4, 2};

  //  float a[4][4] = { 4, -1, 2, 3, 0, -2, 7, -4, 0, 0, 6, 5, 0, 0, 0, 3};
  //  float b[4] = { 20, -7, 4, 6};

    // float a[3][3] = { 5, 4, -1, 0, 10, -3, 0, 0, 1};
    // float b[3] = { 0, 11, 3};

   // float a[3][3] = { 2, 1, 1, 0, -8, -2, 0, 0, 1};
   // float b[3] = { 5, -12, 2};
    //sol: x = (2.5, 1.5, 2)

    float a[3][3] = { -1, 0, 0, 2, 3, 0, -1, 4, -5};
    float b[3] = { -1, 8, -8};
    //sol: x = (1, 2, 3)



    float res[3];

    solve_main( n, a, b, res);
    //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));
     int i,j;
    printf("The res x is \n");
    for( i = 0; i < n; i++) {
        printf(" %f ",res[i]);
    }

    printf("\n");

}
