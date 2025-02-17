#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include "wallet.h"


typedef struct Block {
    unsigned char hash[HASH_SIZE];
    unsigned char miner[PUBLIC_KEY_LENGTH];
    unsigned long int nonce;
    int timestamp;
} Block;




#endif BLOCK_H