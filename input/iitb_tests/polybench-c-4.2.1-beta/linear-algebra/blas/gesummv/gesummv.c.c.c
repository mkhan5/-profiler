
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
/* gesummv.c: this file is part of PolyBench/C */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
#include <polybench.h>

/* Include benchmark-specific header. */
#include "gesummv.h"


/* Array initialization. */
static
void init_array(int n,
		DATA_TYPE *alpha,
		DATA_TYPE *beta,
		DATA_TYPE POLYBENCH_2D(A,N,N,n,n),
		DATA_TYPE POLYBENCH_2D(B,N,N,n,n),
		DATA_TYPE POLYBENCH_1D(x,N,n))
{
  int i, j;

  *alpha = 1;
  *beta = 1;
  for (i = 0; i < n; i++)
    {
      x[i] = (DATA_TYPE)( i % n) / n;
      for (j = 0; j < n; j++) {
	A[i][j] = (DATA_TYPE) ((i*j+1) % n) / n;
	B[i][j] = (DATA_TYPE) ((i*j+2) % n) / n;
      }
    }
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int n,
		 DATA_TYPE POLYBENCH_1D(y,N,n))

{
  int i;

  POLYBENCH_DUMP_START;
  POLYBENCH_DUMP_BEGIN("y");
  for (i = 0; i < n; i++) {
    if (i % 20 == 0) fprintf (POLYBENCH_DUMP_TARGET, "\n");
    fprintf (POLYBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, y[i]);
  }
  POLYBENCH_DUMP_END("y");
  POLYBENCH_DUMP_FINISH;
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static
void kernel_gesummv(int n,
		    DATA_TYPE alpha,
		    DATA_TYPE beta,
		    DATA_TYPE POLYBENCH_2D(A,N,N,n,n),
		    DATA_TYPE POLYBENCH_2D(B,N,N,n,n),
		    DATA_TYPE POLYBENCH_1D(tmp,N,n),
		    DATA_TYPE POLYBENCH_1D(x,N,n),
		    DATA_TYPE POLYBENCH_1D(y,N,n))
{
  int i, j;

//#pragma scop
    cublasStatus_t status;
    cublasHandle_t handle;
    double *d_A = 0;
    double *d_x = 0;
    double *d_y = 0;
    double *d_B = 0;
    double *d_Temp = 0;
    const double d_beta = 0.0f;

    cublasCreate(&handle);
    cudaMalloc((void **)&d_A, n * n * sizeof(d_A[0]));
    cudaMalloc((void **)&d_B,  n * n * sizeof(d_B[0]));
    cudaMalloc((void **)&d_x,  n * sizeof(d_x[0]));
    cudaMalloc((void **)&d_Temp,  n * sizeof(d_Temp[0]));
    cudaMalloc((void **)&d_y,  n * sizeof(d_y[0]));

    cudaMemcpy(d_A, A,  n * n * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B,  n * n * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, n * sizeof(double), cudaMemcpyHostToDevice);

    cublasDgemv(handle, CUBLAS_OP_T, n, n, &alpha, d_A, n, d_x, 1, &d_beta, d_Temp, 1);
    cublasDgemv(handle, CUBLAS_OP_T, n, n, &alpha, d_B, n, d_x, 1, &d_beta, d_y, 1);
    cublasDaxpy(handle, n, &alpha, d_Temp, 1, d_y, 1);

    cudaMemcpy(y, d_y, n*sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_x);
    cudaFree(d_y);
    cudaFree(d_Temp);
    cublasDestroy(handle);

}


int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int n = N;

  /* Variable declaration/allocation. */
  DATA_TYPE alpha;
  DATA_TYPE beta;
  POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
  POLYBENCH_2D_ARRAY_DECL(B, DATA_TYPE, N, N, n, n);
  POLYBENCH_1D_ARRAY_DECL(tmp, DATA_TYPE, N, n);
  POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
  POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);


  /* Initialize array(s). */
  init_array (n, &alpha, &beta,
	      POLYBENCH_ARRAY(A),
	      POLYBENCH_ARRAY(B),
	      POLYBENCH_ARRAY(x));

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_gesummv (n, alpha, beta,
		  POLYBENCH_ARRAY(A),
		  POLYBENCH_ARRAY(B),
		  POLYBENCH_ARRAY(tmp),
		  POLYBENCH_ARRAY(x),
		  POLYBENCH_ARRAY(y));

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(y)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(A);
  POLYBENCH_FREE_ARRAY(B);
  POLYBENCH_FREE_ARRAY(tmp);
  POLYBENCH_FREE_ARRAY(x);
  POLYBENCH_FREE_ARRAY(y);

  return 0;
}
