#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sha256.h"
#include "sha256.c"

//long to string
unsigned char * lts(unsigned long int * numPtr){
    unsigned char * byteArr = (unsigned char *)malloc(8);
    
    memcpy(byteArr, (void*)numPtr, 8);
}

unsigned char * sha256_int(unsigned long int input){
    SHA256_CTX ctx;
    unsigned char * hashBuff = (unsigned char*)malloc(SHA256_BLOCK_SIZE);

    //convert int into bytearray
    unsigned char * byteArr = lts(&input);

    sha256_init(&ctx);
	sha256_update(&ctx, byteArr, strlen(byteArr));
	sha256_final(&ctx, hashBuff);
    
    return hashBuff;
}

//take char array and lenght and output hash
unsigned char * sha256_str(unsigned char * input, int length){
    SHA256_CTX ctx;
    unsigned char * hashBuff = (unsigned char*)malloc(SHA256_BLOCK_SIZE);

    sha256_init(&ctx);
	sha256_update(&ctx, input, length);
	sha256_final(&ctx, hashBuff);

    return hashBuff;
}