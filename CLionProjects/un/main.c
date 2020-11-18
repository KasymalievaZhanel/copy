#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int main (int argc, char * argv[]) {
    long z = strtoll(argv[1], NULL, 27);
    float x;
    u_int64_t y;
    scanf("%f %lx", &x, &y);
    int dec = y;
    printf("%.3f\n", x +(float)dec + z);
    return 0;
}
