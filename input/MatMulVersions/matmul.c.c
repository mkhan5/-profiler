
/* Header below added by Tulsi for replaced OpenMP code */
#include <omp.h>
#include "mkl.h"



/*
 * Multiplication of 2 matrices represented as 2-D arrays
 * Implementation type - using simple three nested loops
 */

#include <stdio.h>

int n=10;


void print(float a[10][10])
{
	int i, j, k;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			printf("%f\t", a[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int main()
{
	int i, j, k;
	float a[10][10], b[10][10], c[10][10];
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			a[i][j] = i;
			b[i][j] = 1;
			c[i][j] = 0;
		}
	}

	print(a); print(b);


    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, alpha, a, n, b, n, beta, c, n);

	print(c);
}
