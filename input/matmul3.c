/*
  OpenMP implementation of matrix multiplication. Each thread takes care
  a chunk of rows.

  Compile with gcc -O3 -fopenmp omp_matrixmult.c -o omp_matrixmult
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 1200                 // size of square matrix

double **a, **b, **c;
double *a_block, *b_block, *c_block;

void initMatricesMemory()
{
    int i;

    a = (double **) malloc(SIZE*sizeof(double *)); /* matrix a to be multiplied */
    b = (double **) malloc(SIZE*sizeof(double *)); /* matrix b to be multiplied */
    c = (double **) malloc(SIZE*sizeof(double *)); /* result matrix c */

    a_block = (double *) malloc(SIZE*SIZE*sizeof(double)); /* Storage for matrices */
    b_block = (double *) malloc(SIZE*SIZE*sizeof(double));
    c_block = (double *) malloc(SIZE*SIZE*sizeof(double));

    for (i=0; i<SIZE; i++)   /* Initialize pointers to a */
        a[i] = a_block+i*SIZE;

    for (i=0; i<SIZE; i++)   /* Initialize pointers to b */
        b[i] = b_block+i*SIZE;

    for (i=0; i<SIZE; i++)   /* Initialize pointers to c */
        c[i] = c_block+i*SIZE;
}

void initMatricesValues()
{
    int i, j;

    for (i=0; i<SIZE; i++) /* last matrix has been initialized */
        for (j=0; j<SIZE; j++)
            a[i][j]= (double) (i+j);

    for (i=0; i<SIZE; i++)
        for (j=0; j<SIZE; j++)
            b[i][j]= (double) (i*j);

    for (i=0; i<SIZE; i++)
        for (j=0; j<SIZE; j++)
            c[i][j]= 0.0;
}

void matrixMultiply()
{
    int i, j, k;
    for (i=0; i<SIZE; i++)
    {
        for (j=0; j<SIZE; j++)
        {
            c[i][j] = 0.0;
            for (k=0; k<SIZE; k++)
                c[i][j] += a[i][k]*b[k][j];
        }
    }
}

void printResultMatrix()
{
    int i, j;
    printf("Result Matrix:\n");
    for (i=SIZE-10; i<SIZE; i++)
    {
        for (j=SIZE-10; j<SIZE; j++)
            printf("%6.1f ", c[i][j]);
        printf("\n");
    }
}

int main (int argc, char *argv[])
{
    initMatricesMemory();
    initMatricesValues();
    matrixMultiply();
    printResultMatrix();

    printf ("Done.\n");
    exit(0);
}



