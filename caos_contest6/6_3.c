#include <stdio.h>
#include <immintrin.h>
#include <stdlib.h>



int main(){
  int N, M;
  scanf("%d %d", &N, &M);
  int aligned_M = M/4*4+4;
  float* A = (float*)malloc(sizeof(float)*N*aligned_M);
  float* B = (float*)malloc(sizeof(float)*N*aligned_M);
  float* res = (float*)malloc(sizeof(float)*N*aligned_M);
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < aligned_M; ++j) {
      if (j >= M) {
        *(A+(i*aligned_M+j)) = 0.;
        continue;
      }
      float x = 0.;
      scanf("%f", &x);
      *(A+(i*aligned_M+j)) = x;
    }
  }

  for(size_t i = 0; i < aligned_M; ++i) {
    for (size_t j = 0; j < N; ++j){
      if (i*j > N*M) {
        *(B+(i+j*aligned_M)) = 0.;
        continue;
      }
      float x = 0.;
      scanf("%f", &x);
      *(B+(i+j*aligned_M)) = x;
    }
  }

  __m128 sum1, sum2;
  float* tmp = (float*)malloc(sizeof(float));
  for (size_t i = 0; i < N; ++i) {
    for(size_t k = 0; k < N; ++k) {
      for (size_t j = 0; j < aligned_M; j+=4) {
        sum1 = _mm_load_ps(&A[i*aligned_M + j]);
        sum2 = _mm_load_ps(&B[k*aligned_M + j]);
        sum2  = _mm_dp_ps(sum1, sum2, 0xF1);
        _mm_store_ps(tmp, sum2);
        *(res+(i*N+k)) += *tmp;
      }
    }
  }
  free(tmp);  

  for (size_t i = 0; i < N * N; ++i) {
    printf("%.4f ", *(res+i));
    if (i == N - 1) 
      printf("\n");
  }
  free(A); free(B); free(res);
  return 0;
}
