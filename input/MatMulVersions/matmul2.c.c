/* Header below added by Tulsi for replaced OpenMP code */
#include <omp.h>
#include "mkl.h"

/*
 * Multiplication of 2 matrices represented as 1-D arrays
 * Implementation type - using simple three nested loops and explicit
 * 	addressing
 */

#include <stdio.h>
#include <stdlib.h>

int N=10;

void print(float a[10])
{
	int i, j, k;
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			printf("%f\t", a[i*N + j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int main()
{
	int i, j, k;
	float *a, *b, *c;
	a = (float *) malloc(N*N*sizeof(float*));
	b = (float *) malloc(N*N*sizeof(float*));
	c = (float *) malloc(N*N*sizeof(float*));

	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			a[i*N + j] = i;
			b[i*N + j] = 1;
			c[i*N + j] = 0;
		}
	}

	print(a); print(b);

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, alpha, a, N, b, N, beta, c, N);

	print(c);
}
