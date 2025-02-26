#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include "wallet.h"


typedef struct Block {
    int timestamp; 
    int transaction_num;
    int height;
    unsigned long long int nonce;
    unsigned long long int difficulty;
    unsigned char hash[HASH_SIZE];
    unsigned char proof[HASH_SIZE];
    unsigned char prev_block_hash[HASH_SIZE];
    unsigned char miner[PUBLIC_KEY_LENGTH];
    Transaction * txs;
} Block;


void init_block(Block *, Wallet *, unsigned long long int, int);
void add_transaction_to_block(Block *, Transaction *);
unsigned char * get_block_hash(Block*);
void complete_block(Block *); 
int write_block_to_file(Block*, char*);
Block * read_blocks_from_file(char*, int);
void complete_block(Block *);
void free_block(Block*);

#endif