#include <stdio.h>
#include <stdlib.h>

int N=2000;

static void simple_sgemm(int n, float alpha, float *A, float *B, float beta, float *C)
{
    int i;
    int j;
    int k;

    float prod;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            prod = 0;

            for (k = 0; k < n; ++k)
            {
                prod += B[k * n + i] * A[j * n + k];
            }

            C[j * n + i] = alpha * prod + beta * C[j * n + i];
        }
    }
}

int main(int argc, char **argv)
{
    float *h_A, *h_B;
    float *h_C;
    float *h_C_ref;
    float alpha = 1.0f;
    float beta = 0.0f;
    int n2 = N * N;
    int i;

    printf("simpleCUBLAS test running..\n");

    /* Allocate host memory for the matrices */
    h_A = (float *)malloc(n2 * sizeof(h_A[0]));
    h_B = (float *)malloc(n2 * sizeof(h_B[0]));

    if (h_B == 0)
    {
        fprintf(stderr, "!!!! host memory allocation error (B)\n");
        return EXIT_FAILURE;
    }

    h_C = (float *)malloc(n2 * sizeof(h_C[0]));

    if (h_C == 0)
    {
        fprintf(stderr, "!!!! host memory allocation error (C)\n");
        return EXIT_FAILURE;
    }

    /* Fill the matrices with test data */
    for (i = 0; i < n2; i++)
    {
        h_A[i] = rand() / (float)RAND_MAX;
        h_B[i] = rand() / (float)RAND_MAX;
        h_C[i] = rand() / (float)RAND_MAX;
    }

    /* Performs operation using plain C code */
    simple_sgemm(N, alpha, h_A, h_B, beta, h_C);

    /* Memory clean up */
    free(h_A);
    free(h_B);
    free(h_C);
}
