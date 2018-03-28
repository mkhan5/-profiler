
/* Header below added by Tulsi for replaced CUBLAS code */
#include <cuda_runtime.h>
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
/* mvt.c: this file is part of PolyBench/C */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
#include <polybench.h>

/* Include benchmark-specific header. */
#include "mvt.h"


/* Array initialization. */
static
void init_array(int n,
		DATA_TYPE POLYBENCH_1D(x1,N,n),
		DATA_TYPE POLYBENCH_1D(x2,N,n),
		DATA_TYPE POLYBENCH_1D(y_1,N,n),
		DATA_TYPE POLYBENCH_1D(y_2,N,n),
		DATA_TYPE POLYBENCH_2D(A,N,N,n,n))
{
  int i, j;

  for (i = 0; i < n; i++)
    {
      x1[i] = (DATA_TYPE) (i % n) / n;
      x2[i] = (DATA_TYPE) ((i + 1) % n) / n;
      y_1[i] = (DATA_TYPE) ((i + 3) % n) / n;
      y_2[i] = (DATA_TYPE) ((i + 4) % n) / n;
      for (j = 0; j < n; j++)
	A[i][j] = (DATA_TYPE) (i*j % n) / n;
    }
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int n,
		 DATA_TYPE POLYBENCH_1D(x1,N,n),
		 DATA_TYPE POLYBENCH_1D(x2,N,n))

{
  int i;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("x1");
  for (i = 0; i < n; i++) {
    if (i % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
    fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, x1[i]);
  }
  POLYBENCH_DUMP_END("x1");

  POLYBENCH_DUMP_BEGIN("x2");
  for (i = 0; i < n; i++) {
    if (i % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
    fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, x2[i]);
  }
  POLYBENCH_DUMP_END("x2");
  POLYBENCH_DUMP_FINISH;
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static
void kernel_mvt(int n,
		DATA_TYPE POLYBENCH_1D(x1,N,n),
		DATA_TYPE POLYBENCH_1D(x2,N,n),
		DATA_TYPE POLYBENCH_1D(y_1,N,n),
		DATA_TYPE POLYBENCH_1D(y_2,N,n),
		DATA_TYPE POLYBENCH_2D(A,N,N,n,n))
{
  int i, j;

//#pragma scop


    cublasStatus_t status;
    cublasHandle_t handle;
    double *d_A = 0;
    double *d_x1 = 0;
    double *d_x2 = 0;
    double *d_y1 = 0;
    double *d_y2 = 0;
    const double cublas_alpha = 1.0;
    const double cublas_beta = 1.0;

    cublasCreate(&handle);
    cudaMalloc((void **)&d_A, n * n * sizeof(d_A[0]));
    cudaMalloc((void **)&d_x1,  n * sizeof(d_x1[0]));
    cudaMalloc((void **)&d_x2,  n * sizeof(d_x2[0]));
    cudaMalloc((void **)&d_y1,  n * sizeof(d_y1[0]));
    cudaMalloc((void **)&d_y2,  n * sizeof(d_y2[0]));

    cudaMemcpy(d_A, A,  n * n * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x1, x1, n * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x2, x2, n * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y1, y_1, n * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y2, y_2, n * sizeof(double), cudaMemcpyHostToDevice);


    cublasDgemv(handle, CUBLAS_OP_T, n, n, &cublas_alpha, d_A, n, d_y1, 1, &cublas_beta, d_x1, 1);
    cublasDgemv(handle, CUBLAS_OP_N, n, n, &cublas_alpha, d_A, n, d_y2, 1, &cublas_beta, d_x2, 1);
    cudaMemcpy( x1, d_x1, n*sizeof(double), cudaMemcpyDeviceToHost);
    cudaMemcpy( x2, d_x2, n*sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(d_A);
    cudaFree(d_x1);
    cudaFree(d_x2);
    cudaFree(d_y1);
    cudaFree(d_y2);
    cublasDestroy(handle);

}


int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int n = N;

  /* Variable declaration/allocation. */
  POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
  POLYBENCH_1D_ARRAY_DECL(x1, DATA_TYPE, N, n);
  POLYBENCH_1D_ARRAY_DECL(x2, DATA_TYPE, N, n);
  POLYBENCH_1D_ARRAY_DECL(y_1, DATA_TYPE, N, n);
  POLYBENCH_1D_ARRAY_DECL(y_2, DATA_TYPE, N, n);


  /* Initialize array(s). */
  init_array (n,
	      POLYBENCH_ARRAY(x1),
	      POLYBENCH_ARRAY(x2),
	      POLYBENCH_ARRAY(y_1),
	      POLYBENCH_ARRAY(y_2),
	      POLYBENCH_ARRAY(A));

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_mvt (n,
	      POLYBENCH_ARRAY(x1),
	      POLYBENCH_ARRAY(x2),
	      POLYBENCH_ARRAY(y_1),
	      POLYBENCH_ARRAY(y_2),
	      POLYBENCH_ARRAY(A));

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(x1), POLYBENCH_ARRAY(x2)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(A);
  POLYBENCH_FREE_ARRAY(x1);
  POLYBENCH_FREE_ARRAY(x2);
  POLYBENCH_FREE_ARRAY(y_1);
  POLYBENCH_FREE_ARRAY(y_2);

  return 0;
}
