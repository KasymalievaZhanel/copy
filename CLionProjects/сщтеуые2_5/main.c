#include <stdio.h>
#include <stdint.h>

int number_of_bytes(int a) {
    if ((a >> 5) == 6)
        return 2;
    if ((a >> 4) == 14)
        return 3;
    if ((a >> 3) == 30)
        return 4;
    else return 0;
}

int main() {
    int64_t input = 0;
    int64_t ascii = 0;
    int64_t utf = 0;
    while ((input = getchar()) != EOF) {
        if ((input & (1 << 7)) == 0)
            ascii ++;
        else {
            int64_t error = number_of_bytes(input);
            if (error < 1 || error > 4) {
                printf("%ld %ld", ascii, utf);
                return 1;
            }
            int64_t symbol;
            for (int64_t i = 1; i < error; ++i) {
                if ((symbol = getchar()) == EOF) {
                    printf("%ld %ld", ascii, utf);
                    return 1;
                }
                if((symbol >> 6) != 2) {
                    printf("%ld %ld", ascii, utf);
                    return 1;
                }
            }
            utf ++;
        }
    }
    printf("%ld %ld", ascii, utf);
    return 0;
}