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
	for(jj=0; jj<N; jj+= TILE) {
		for( kk=0; kk<N; kk+= TILE) {
			for(i=0; i<N; i++) {
				for(j = jj; j<((jj+TILE)>N?N:(jj+TILE)); j++) {
					temp = 0;
					for(k = kk; k<((kk+TILE)>N?N:(kk+TILE)); k++) {
						temp += a[i][k]*b[k][j];
					}
					c[i][j] = temp;
				}
			}
		}
	}

	print(c);
}
