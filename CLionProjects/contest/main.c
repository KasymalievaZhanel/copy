#include<stdint.h>


typedef union {
    double     real_value;
    uint64_t   uint_value;
} real_or_uint;


typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;


float_class_t classify(double *value_ptr){
    real_or_uint  u;
    u.real_value = *value_ptr;
    uint64_t b = u.uint_value;
//    for(uint64_t i = 0; i < 64; ++i){
//        printf("%d", (((1ULL<<(63 - i)) & b) >> (63-i)));
//    }
//    printf("\n");
    if (b == 0ULL)
        return PlusZero;
    else if (b == 9223372036854775808LLU)
        return MinusZero;
        //1000000000000000000000000000000000000000000000000000000000000000 = 9223372036854775808
    else if ( b == 9218868437227405312LLU)
        return PlusInf;
        //0111111111110000000000000000000000000000000000000000000000000000 = 9218868437227405312
    else if (b == 18442240474082181120LLU)
        return MinusInf;
    else if ((b & 18442240474082181120ULL) == 9218868437227405312LLU && (b & 4503599627370495LLU) != 0)
        return SignalingNaN;
    else if ((b & 18442240474082181120LLU) == 18442240474082181120LLU && (b & 4503599627370495LLU) != 0)
        return QuietNaN;
    else if (b > 0 && b <= 2251799813685248)
        return PlusDenormal;
    else if((b & 18442240474082181120LLU) == 9223372036854775808LLU && (b & 4503599627370495LLU) != 0)
        return MinusDenormal;
    else if((((1ULL<< 63) & b) >> 63) == 1)
        return MinusRegular;
    else if((((1ULL<< 63) & b) >> 63) == 0)
        return PlusRegular;
    else
        return 0;
}


