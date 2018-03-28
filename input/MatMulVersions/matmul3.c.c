
/* Header below added by Tulsi for replaced OpenMP code */
#include <omp.h>
#include "mkl.h"



/*
 * Multiplication of 2 matrices represented as 2-D arrays
 * Implementation type - using partial tiling and outerloop interchange
 */

#include <stdio.h>

int N=5;

/* block size */
int TILE=3;

void print(float a[5][5])
{
	int i, j, k;
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			printf("%f\t", a[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int main()
{
	int i, j, k;
	float a[5][5], b[5][5], c[5][5];
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			a[i][j] = i;
			b[i][j] = 1;
			c[i][j] = 0;
		}
	}

	print(a); print(b);

	float temp;
	int jj, kk;

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, alpha, a, N, b, N, beta, c, N);

	print(c);
}
