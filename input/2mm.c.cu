
/* Header below added by Tulsi for replaced CUBLAS code */
#include <cuda_runtime.h>
#include <cublas_v2.h>


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
//#define N 3
int N=3;

void mm2( double A[N][N],
            double B[N][N],
            double C[N][N],
            double D[N][N],
            double tmp[N][N],
            double alpha,
            double beta
           )
{
  int i, j,k;

  /* D := alpha*A*B*C + beta*D */
    
    cublasStatus_t status;
    cublasHandle_t handle;
    double *d_A = 0;
    double *d_B = 0;
    double *d_C = 0;
    double *d_D = 0;
    double *d_tmpAB = 0;
    const double cublas_alpha = 1.0f;
    const double cublas_beta = 0.0f;
    cublasCreate(&handle);
    
    cudaMalloc((void **)&d_A, N * N * sizeof(d_A[0]));
    cudaMalloc((void **)&d_B, N * N * sizeof(d_B[0]));
    cudaMalloc((void **)&d_C, N * N * sizeof(d_C[0]));
    cudaMalloc((void **)&d_D, N * N * sizeof(d_D[0]));
    cudaMalloc((void **)&d_tmpAB, N * N * sizeof(d_tmpAB[0]));
    
    cudaMemcpy(d_A, A,  N * N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, N *N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, C, N *N * sizeof(double), cudaMemcpyHostToDevice);
    
    cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, N, N, N, &cublas_alpha, d_B, N, d_A, N, &cublas_beta, d_tmpAB, N);
    cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, N, N, N, &cublas_alpha, d_C, N, d_tmpAB, N, &cublas_beta, d_D, N);
    cudaMemcpy(D, d_D, N*N*sizeof(double), cudaMemcpyDeviceToHost);
    
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    cudaFree(d_D);
    cudaFree(d_tmpAB);
    cublasDestroy(handle);

}


int main(int argc, char** argv)
{

  int M = 3;


  double a[3][3] = { 1, 2, 5, 9, 23, -7, 6, 1, -3};
  double b[3][3] = { 17, 2, -1, -12, -19, -22, -1, 3, 9};
  double c[3][3] = {1, 5, -1, -2, 1, 21, -30, -11, -15};
  double tmp[3][3];
  double d[3][3];
  //sol: y = (13, 31, 49)
  double alpha = 1;
  double beta = 0;

  mm2(a, b, c, d, tmp, alpha, beta);
  //std::copy( res, res + 3, std::ostream_iterator<float>( std::cout, ","));
  int i,j;
  printf("The res x is \n");
  for( i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
      {
        printf(" %f ",d[i][j]);
       }
       printf("\n");
    }

  printf("\n");

}
