#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; ++i) {
        uint64_t value = strtoll(argv[i], NULL, 16);
          for(uint64_t i = 0; i <= 63; ++i) {
               printf("%lld", ((1ULL<< (63 - i)) & value)>>(63 - i));
           }
           printf("\n");
        if (value != 0) {
            int bites = 0;
            int k = 0;
            while (value != 0) {
                (value >>= 1);
                ++bites;
                for(uint64_t i = 0; i <= 63; ++i) {
                    printf("%lld", ((1ULL<< (63 - i)) & value)>>(63 - i));
                }
                printf("\n");

            }
                printf("%d\n", bites);
            while (bites % 8 != 0) {
                ++bites;
            }
            printf("%d ", bites / 8);
        } else
            printf("1 ");
    }
    return 0;
}
