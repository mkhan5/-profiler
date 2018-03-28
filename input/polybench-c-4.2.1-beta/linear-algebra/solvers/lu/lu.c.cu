
/* Header below added by Tulsi for replaced CUBLAS code */
#include "cuda_runtime.h"
#include <cusolverDn.h>
#include <cublas_v2.h>


/**
 * This version is stamped on May 10, 2016
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://polybench.sourceforge.net
 */
/* lu.c: this file is part of PolyBench/C */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
#include <polybench.h>

/* Include benchmark-specific header. */
#include "lu.h"


/* Array initialization. */
static
void init_array (int n,
		 DATA_TYPE POLYBENCH_2D(A,N,N,n,n))
{
  int i, j;

  for (i = 0; i < n; i++)
    {
      for (j = 0; j <= i; j++)
	A[i][j] = (DATA_TYPE)(-j % n) / n + 1;
      for (j = i+1; j < n; j++) {
	A[i][j] = 0;
      }
      A[i][i] = 1;
    }

  /* Make the matrix positive semi-definite. */
  /* not necessary for LU, but using same code as cholesky */
  int r,s,t;
  POLYBENCH_2D_ARRAY_DECL(B, DATA_TYPE, N, N, n, n);
  for (r = 0; r < n; ++r)
    for (s = 0; s < n; ++s)
      (POLYBENCH_ARRAY(B))[r][s] = 0;
  for (t = 0; t < n; ++t)
    for (r = 0; r < n; ++r)
      for (s = 0; s < n; ++s)
	(POLYBENCH_ARRAY(B))[r][s] += A[r][t] * A[s][t];
    for (r = 0; r < n; ++r)
      for (s = 0; s < n; ++s)
	A[r][s] = (POLYBENCH_ARRAY(B))[r][s];
  POLYBENCH_FREE_ARRAY(B);

}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int n,
		 DATA_TYPE POLYBENCH_2D(A,N,N,n,n))

{
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("A");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if ((i * n + j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
      fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, A[i][j]);
    }
  POLYBENCH_DUMP_END("A");
  POLYBENCH_DUMP_FINISH;
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static
void kernel_lu(int n,
	       DATA_TYPE POLYBENCH_2D(A,N,N,n,n))
{
  int i, j, k;

//#pragma scop
    double *d_A,*d_B,*d_AT;
    const double cublas_alpha = 1.0;
    const double cublas_beta = 0.0;
    cublasHandle_t handle;
    cublasCreate(&handle);

    cudaMalloc((void **)&d_A, n * n * sizeof(double));
    cudaMalloc((void **)&d_AT, n * n * sizeof(double));

    cudaMemcpy(d_A, A, n * n * sizeof(double), cudaMemcpyHostToDevice);
    cublasDgeam(handle,CUBLAS_OP_T, CUBLAS_OP_N, n, n, &cublas_alpha, d_A, n, &cublas_beta, d_B, n, d_AT, n);

    int worksize = 0;
    int *devInfo;
    cudaMalloc((void **)&devInfo, sizeof(int));
    cusolverDnHandle_t solver_handle;
    cusolverDnCreate(&solver_handle);

    cusolverDnDgetrf_bufferSize(solver_handle, n, n, d_AT, n, &worksize);
    double *work;
    cudaMalloc((void **)&work, worksize * sizeof(double));
    int *devIpiv;
    cudaMalloc((void **)&devIpiv, n * sizeof(int));

    cusolverDnDgetrf(solver_handle, n, n, d_AT, n, work, devIpiv, devInfo);
    int devInfo_h = 0;
    cudaMemcpy(&devInfo_h, devInfo, sizeof(int), cudaMemcpyDeviceToHost);
    if (devInfo_h != 0)
        printf("Unsuccessful getrf execution\n\n");
    printf("\nFactorized matrix\n");

    cublasDgeam(handle,CUBLAS_OP_T, CUBLAS_OP_N, n, n, &cublas_alpha, d_AT, n, &cublas_beta, d_B, n, d_A, n);
    cudaMemcpy(A, d_A, n * n * sizeof(double), cudaMemcpyDeviceToHost);
    cublasDestroy(handle);
    cudaFree(d_A);
    cudaFree(d_AT);
    cudaFree(devInfo);
    cudaFree(work);
    cudaFree(devIpiv);
    cusolverDnDestroy(solver_handle);
//#pragma endscop
}


int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int n = N;

  /* Variable declaration/allocation. */
  POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);

  /* Initialize array(s). */
  init_array (n, POLYBENCH_ARRAY(A));

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_lu (n, POLYBENCH_ARRAY(A));

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(A)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(A);

  return 0;
}
