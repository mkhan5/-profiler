/* 
 * Multiplication of 2 matrices represented as 1-D arrays
 * Implementation type - using tiling and inner loop interchange
 */

#include <stdio.h>
#include <stdlib.h>

int n=10;
int N = 10;
int TILE=3;

void print(float a[10])
{
	int i, j, k;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			printf("%f\t", a[i*n + j]);
		}
		printf("\n");
	}
	printf("\n\n");
}	

int main()
{
	int i, j, k;
	int x, y, z;
	float *a, *b, *c, prod;
	
	a = (float *) malloc(n*n*sizeof(float*));
	b = (float *) malloc(n*n*sizeof(float*));
	c = (float *) malloc(n*n*sizeof(float*));
	
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			a[i*n + j] = i;
			b[i*n + j] = 1;
			c[i*n + j] = 0;
		}
	}
	
//	print(a); print(b);

	for (i=0; i<N; i+=TILE)
		for (j=0; j<N; j+=TILE)
			for (k=0; k<N; k+=TILE)
				for (y=i; y<i+TILE && y<N; y++)
					for (x=j; x<j+TILE && x<N; x++) {
						prod = 0;
						for (z=k; z<k+TILE && z<N; z++)
							prod += a[y*(N)+z]*b[z*(N)+x];
						c[y*(N)+x] = prod;
					}

	print(c);
}
