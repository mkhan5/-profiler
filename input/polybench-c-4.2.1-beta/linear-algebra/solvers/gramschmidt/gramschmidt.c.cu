
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
/* gramschmidt.c: this file is part of PolyBench/C */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
#include <polybench.h>

/* Include benchmark-specific header. */
#include "gramschmidt.h"


/* Array initialization. */
static
void init_array(int m, int n,
		DATA_TYPE POLYBENCH_2D(A,M,N,m,n),
		DATA_TYPE POLYBENCH_2D(R,N,N,n,n),
		DATA_TYPE POLYBENCH_2D(Q,M,N,m,n))
{
  int i, j;

  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) {
      A[i][j] = (((DATA_TYPE) ((i*j) % m) / m )*100) + 10;
      Q[i][j] = 0.0;
    }
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++)
      R[i][j] = 0.0;
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int m, int n,
		 DATA_TYPE POLYBENCH_2D(A,M,N,m,n),
		 DATA_TYPE POLYBENCH_2D(R,N,N,n,n),
		 DATA_TYPE POLYBENCH_2D(Q,M,N,m,n))
{
  int i, j;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("R");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
	if ((i*n+j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, R[i][j]);
    }
  POLYBENCH_DUMP_END("R");

  POLYBENCH_DUMP_BEGIN("Q");
  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) {
	if ((i*n+j) % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
	fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, Q[i][j]);
    }
  POLYBENCH_DUMP_END("Q");
  POLYBENCH_DUMP_FINISH;
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
/* QR Decomposition with Modified Gram Schmidt:
 http://www.inf.ethz.ch/personal/gander/ */
static
void kernel_gramschmidt(int m, int n,
			DATA_TYPE POLYBENCH_2D(A,M,N,m,n),
			DATA_TYPE POLYBENCH_2D(R,N,N,n,n),
			DATA_TYPE POLYBENCH_2D(Q,M,N,m,n))
{
  int i, j, k;

  DATA_TYPE nrm;

//#pragma scop
    int i,j,k;
    double *d_A,*d_AT,*d_Q,*d_B;
    const double cublas_alpha = 1.0;
    const double cublas_beta = 0.0;
    cublasHandle_t handle;

    cublasCreate(&handle);
    cudaMalloc((void **)&d_A,      m * m * sizeof(double));
    cudaMalloc((void **)&d_Q,      m * m * sizeof(double));
    cudaMemcpy(d_A, A, m * m * sizeof(double), cudaMemcpyHostToDevice);
    cudaMalloc((void **)&d_AT,      m * m * sizeof(double));

    cublasDgeam(handle,CUBLAS_OP_T, CUBLAS_OP_N, m, m, &cublas_alpha, d_A, m, &cublas_beta, d_B, m, d_AT, m);

    int worksize = 0;
    int *devInfo;
    cudaMalloc((void **)&devInfo, sizeof(int));
    cusolverDnHandle_t solver_handle;
    cusolverDnCreate(&solver_handle);

    cusolverDnDgeqrf_bufferSize(solver_handle, m, m, d_AT, m, &worksize);
    double *work;
    cudaMalloc((void **)&work, worksize * sizeof(double));
    double *TAU;
    cudaMalloc((void **)&TAU, m * sizeof(double));

    cusolverDnDgeqrf(solver_handle, m, m, d_AT, m, TAU, work, worksize, devInfo);

    int devInfo_h = 0;
    cudaMemcpy(&devInfo_h, devInfo, sizeof(int), cudaMemcpyDeviceToHost);
    if (devInfo_h != 0)
        printf("Unsuccessful geqrf execution\n\n");
    double *q_h;
    q_h = (double *)malloc( m*m*sizeof( double ));
    printf("\nFactorized matrix\n");

    cublasDgeam(handle,CUBLAS_OP_T, CUBLAS_OP_N, m, m, &cublas_alpha, d_AT, m, &cublas_beta, d_B, m, d_A, m);
    cudaMemcpy(R, d_A, m * m * sizeof(double), cudaMemcpyDeviceToHost);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            q_h[i*m+j] = 0.0;
            if (i==j)
                q_h[i*m+j] = 1.0;
        }
    }

    cudaMemcpy(d_Q, q_h, m * m * sizeof(double), cudaMemcpyHostToDevice);
    cusolverDnDormqr(solver_handle,CUBLAS_SIDE_LEFT, CUBLAS_OP_T, m, m, m, d_AT, m, TAU, d_Q, m, work, worksize, devInfo);

    devInfo_h = 0;
    cudaMemcpy(&devInfo_h, devInfo, sizeof(int), cudaMemcpyDeviceToHost);
    if (devInfo_h != 0)
        printf("Unsuccessful ormqr execution\n\n");
    cudaMemcpy(Q, d_Q, m * m * sizeof(double), cudaMemcpyDeviceToHost);
    cublasDestroy(handle);
    cudaFree(d_A);
    cudaFree(d_AT);
    cudaFree(d_Q);
    cudaFree(TAU);
    cudaFree(work);
    cudaFree(devInfo);
    cusolverDnDestroy(solver_handle);

}


int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int m = M;
  int n = N;

  /* Variable declaration/allocation. */
  POLYBENCH_2D_ARRAY_DECL(A,DATA_TYPE,M,N,m,n);
  POLYBENCH_2D_ARRAY_DECL(R,DATA_TYPE,N,N,n,n);
  POLYBENCH_2D_ARRAY_DECL(Q,DATA_TYPE,M,N,m,n);

  /* Initialize array(s). */
  init_array (m, n,
	      POLYBENCH_ARRAY(A),
	      POLYBENCH_ARRAY(R),
	      POLYBENCH_ARRAY(Q));

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_gramschmidt (m, n,
		      POLYBENCH_ARRAY(A),
		      POLYBENCH_ARRAY(R),
		      POLYBENCH_ARRAY(Q));

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(m, n, POLYBENCH_ARRAY(A), POLYBENCH_ARRAY(R), POLYBENCH_ARRAY(Q)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(A);
  POLYBENCH_FREE_ARRAY(R);
  POLYBENCH_FREE_ARRAY(Q);

  return 0;
}
