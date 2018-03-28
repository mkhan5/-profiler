
/* Header below added by Tulsi for replaced CUBLAS code */
#include <cuda_runtime.h>
#include <cublas_v2.h>


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


//#define N 3
int N=3;

void mvt( double A[N][N],
           double x1[N],
           double x2[N],
           double y_1[N],
           double y_2[N])
{
  int i, j;



    cublasStatus_t status;
    cublasHandle_t handle;
    double *d_A = 0;
    double *x1 = 0;
    double *x2 = 0;
    double *y1 = 0;
    double *y2 = 0;
    const double cublas_alpha = 1.0;
    const double cublas_beta = 1.0;

    cublasCreate(&handle);
    cudaMalloc((void **)&d_A, N * N * sizeof(d_A[0]));
    cudaMalloc((void **)&x1,  N * sizeof(x1[0]));
    cudaMalloc((void **)&x2,  N * sizeof(x2[0]));
    cudaMalloc((void **)&y1,  N * sizeof(y1[0]));
    cudaMalloc((void **)&y2,  N * sizeof(y2[0]));

    cudaMemcpy(d_A, A,  N * N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(x1, x1, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(x2, x2, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(y1, y_1, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(y2, y_2, N * sizeof(double), cudaMemcpyHostToDevice);


    cublasDgemv(handle, CUBLAS_OP_T, N, N, &cublas_alpha, d_A, N, y1, 1, &cublas_beta, x1, 1);
    cublasDgemv(handle, CUBLAS_OP_N, N, N, &cublas_alpha, d_A, N, y2, 1, &cublas_beta, x2, 1);
    cudaMemcpy( x1, x1, N*sizeof(double), cudaMemcpyDeviceToHost);
    cudaMemcpy( x2, x2, N*sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(d_A);
    cudaFree(x1);
    cudaFree(x2);
    cudaFree(y1);
    cudaFree(y2);
    cublasDestroy(handle);

}


int main(int argc, char** argv)
{

  int M = 4;
  int i,j;

  //double a[4][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 6, 7, 8};
  //double x[4] = { 2, 1, 3, 5};
  double a[3][3] = { 1, -2, 3, 4, 6, 6, -17, -11, 8};
  double x1[3] = { -5, -9, 6};
  double x2[3] = { -2, 3, 21};
  double y1[3] = { -1, -4, 23};
  double y2[3] = { 7, -8, -19};

printf("The x1 is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",x1[i]);
    }

  printf("\n");
  printf("The x2 is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",x2[i]);
    }

  printf("\n");

    mvt(a, x1, x2, y1, y2);
  //std::copy( res, res + 3, std::ostream_iterator<double>( std::cout, ","));

  printf("The res x1 is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",x1[i]);
    }

  printf("\n");
  printf("The res x2 is \n");
  for( i = 0; i < N; i++)
    {
      printf(" %f ",x2[i]);
    }

  printf("\n");

}
