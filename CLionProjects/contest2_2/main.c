#include <stdbool.h>

uint16_t satsum(uint16_t x, uint16_t y){
    uint16_t value = x + y;
    bool overflow = value < (x | y);
    if(overflow == 1)
        return UINT16_MAX;
    else
        return x+y;
}
