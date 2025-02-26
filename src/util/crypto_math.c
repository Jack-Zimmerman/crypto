
#include "crypto_math.h"
#include <stdio.h>


uint256 bignum_from_hex(unsigned char * hex){
    uint256 bignum;

    for (int i = 0; i < UINT_256_LONG_WIDTH; i++) {
        bignum.nums[i] = 0;
        for (int offset = 0; offset < sizeof(unsigned long long int); offset++){
            bignum.nums[i] = (bignum.nums[i] << 8) | hex[i * sizeof(unsigned long long int) + offset];
        }
    }

    return bignum;
}

int main(void){
    unsigned char hexnum[32];
    for (int a = 0; a < 32; a++){
        hexnum[a] = 255;
    }

    uint256 x = bignum_from_hex(hexnum);     

    for (int i = 0; i < 4; i++){
        printf("%llu\n", x.nums[i]);
    }
}