#include "block.h"
#include <time.h>
#include <stdlib.h>


void init_block(Block * block, Wallet * sender, unsigned long int difficulty, int height){
    
    //init known aspects
    block->timestamp = (int)time(NULL);
    block->height = height;
    block->difficulty = difficulty;
    block->transaction_num = 0; 

    //init miner as pubkey of creator
    memcpy(block->miner, sender->pubkey, PUBLIC_KEY_LENGTH);
}


//add transaction to block tx array
void add_transaction_to_block(Block * block, Transaction * tx){
    //increase size of block transactions and incriment tx array
    block->transactions = (Transaction**)realloc(block->transactions, sizeof(Transaction) * (++block->transaction_num));

    block->transactions[block->transaction_num - 1] = tx;
}