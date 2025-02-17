#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include "wallet.h"


typedef struct Block {
    unsigned char hash[HASH_SIZE];
    unsigned char miner[PUBLIC_KEY_LENGTH];
    Transaction ** transactions;
    int transaction_num;
    unsigned long int nonce;
    int height;
    int timestamp; 
    unsigned long int difficulty;
} Block;


void init_block(Block *, Wallet *, long unsigned int, int);
void add_transaction_to_block(Block *, Transaction *);


#endif