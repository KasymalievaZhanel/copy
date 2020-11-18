#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; ++i){
        u_int64_t ch = strtoll(argv[i], NULL, 16);
        double float_ch = (double)ch;
        if (ch != 0) {
            printf("%f\n", log2 (float_ch));
            double bites = (log2(float_ch) > (int) log2(float_ch) ? (int) log2(float_ch) + 1.0 : log2(float_ch));
            printf("%f\n", bites);
            int bytes = (bites / 8 > (int) (bites / 8) ? (int) (bites / 8) + 1 : (int)(bites / 8));
            printf("%d ", bytes);
        }
        else
            printf("1 ");
    }
    return 0;
}
