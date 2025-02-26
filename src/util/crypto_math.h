#ifndef CRYPTO_MATH_H
#define CRYPTO_MATH_H


#define UINT_256_LONG_WIDTH 4 

typedef struct uint256 {
    unsigned long long int nums[UINT_256_LONG_WIDTH];
} uint256;


uint256 bignum_from_uint(unsigned long long int);
uint256 bignum_from_hex(unsigned char*);
uint256 bignum_divide(uint256 num1, uint256 num2);
int bignum_compare(uint256 num1, uint256 num2);


#endif 