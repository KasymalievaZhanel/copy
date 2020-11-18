#include <stdio.h>
#include <stdint.h>

extern int summ(int32_t, int32_t, int32_t*);
/*
int sum(int x, int n, int64_t * arr){
    int summ = 0;
    for(int i = 0; i < n; ++i){
        summ += arr[i];
    }
    summ += x;
    printf("%d", summ);
    return 0;
}
*/
int main() {
    int32_t x0 = 5;
    int32_t N = 10;
    int32_t a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int32_t k = summ(x0, N, a);
    printf("%lu", k);
    return 0;
}

