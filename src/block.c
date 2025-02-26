#include "block.h"
#include "wallet.h"
#include "crypto/hash.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


void init_block(Block * block, Wallet * sender, unsigned long long int difficulty, int height){
    
    Transaction * tx_init;
    //init known aspects
    block->timestamp = (int)time(NULL);
    block->height = height;
    block->difficulty = difficulty;
    block->transaction_num = 0; 
    block->txs = tx_init; 
    
    //init miner as pubkey of creator
    memcpy(block->miner, sender->pubkey, PUBLIC_KEY_LENGTH);
}

//add transaction to block tx array
void add_transaction_to_block(Block * block, Transaction * tx){
    //increase size of block transactions and incriment tx array
    //if not init we give first init, otherwise it would be reallocating a null
    if (block->txs== NULL){
        block->txs = (Transaction*)malloc(sizeof(Transaction));
    }
    else{
        block->txs = (Transaction*)realloc(block->txs, sizeof(Transaction) * (1 + block->transaction_num));
    }

    
    //copy hash in
    block->txs[block->transaction_num++] = *tx;
}


unsigned char * get_block_hash(Block * block){
    //hash_input = 
    //hashes of all transactions
    //timestamp
    //miner pubkey
    int hash_input_size = (block->transaction_num * HASH_SIZE) + (2 * sizeof(int)) + PUBLIC_KEY_LENGTH;
    unsigned char * hash_input = (unsigned char*)malloc(hash_input_size);
    unsigned char * hash;

    //copy hashses into buffer
    for (int i = 0; i < block->transaction_num; i++){
        memcpy(hash_input + (i * HASH_SIZE), block->txs[i].hash, HASH_SIZE);
    }

    memcpy(hash_input + (block->transaction_num * HASH_SIZE), &block->timestamp, sizeof(int));
    memcpy(hash_input + (block->transaction_num * HASH_SIZE) + sizeof(int), &block->height, sizeof(int));
    memcpy(hash_input + (block->transaction_num * HASH_SIZE) + (2*sizeof(int)), block->miner, PUBLIC_KEY_LENGTH);
    


    hash = sha256_str(hash_input, hash_input_size);

    //free buffer
    free(hash_input);

    return hash;
}


//append block struct to file
int write_block_to_file(Block * block,  char * fname){
    FILE * fptr = fopen(fname, "ab");
    
    //if pointer is wrong, return false
    if (!fptr){
        return 0;
    }
    else if (!block->txs){
        return 0; 
    }

    fwrite(&block->timestamp, sizeof(int), 1, fptr);
    fwrite(&block->transaction_num, sizeof(int), 1, fptr);
    fwrite(&block->height, sizeof(int), 1, fptr);
    fwrite(&block->nonce, sizeof(unsigned long long int), 1, fptr);
    fwrite(&block->difficulty, sizeof(unsigned long long int), 1, fptr);
    fwrite(block->hash, HASH_SIZE, 1, fptr);
    fwrite(block->proof, HASH_SIZE, 1, fptr);
    fwrite(block->miner, PUBLIC_KEY_LENGTH, 1, fptr);
    fwrite(block->prev_block_hash, HASH_SIZE, 1, fptr); 
    
    
    //write transaction hash arr, we will know size from block->transaction_num fread beforehand
    for (int i = 0; i < block->transaction_num; i++){
        //deref pointer and give stream
        fwrite(&block->txs[i], sizeof(Transaction), 1, fptr);
    }    
 
        
    fclose(fptr);
    
    //all good
    return 1;
}

Block * read_blocks_from_file(char * fname, int num_blocks){
    Block * block_array = (Block*)malloc(sizeof(Block) * num_blocks);
    FILE * fptr = fopen(fname, "rb");

    if (!fptr){
        return NULL;
    }

    //read blocks
    for (int i = 0; i < num_blocks; i++){
        Block block;

        fread(&block.timestamp, sizeof(int), 1, fptr);
        fread(&block.transaction_num, sizeof(int), 1, fptr);
        fread(&block.height, sizeof(int), 1, fptr);
        fread(&block.nonce, sizeof(unsigned long long int), 1, fptr);
        fread(&block.difficulty, sizeof(unsigned long long int), 1, fptr);
        fread(block.hash, HASH_SIZE, 1, fptr);
        fread(block.proof, HASH_SIZE, 1, fptr);
        fread(block.miner, PUBLIC_KEY_LENGTH, 1, fptr);
        fread(block.prev_block_hash, HASH_SIZE, 1, fptr); 


        
        Transaction * tx_ptr_arr = (Transaction*)malloc(sizeof(Transaction) * block.transaction_num);
        block.txs = tx_ptr_arr;


        //read all the transactions
        for (int a = 0; a < block.transaction_num; a++){
            //generate transaction obj
            Transaction tx;

            fread(&tx, sizeof(Transaction), 1, fptr);

            block.txs[a] = tx;
        }         

        block_array[i] = block;
    }

    fclose(fptr);

    return block_array;
}

void complete_block(Block * block){
    unsigned char hash[HASH_SIZE]; 

    //add hash to block
    memcpy(block->hash, get_block_hash(block), HASH_SIZE);
}

void free_block(Block * block){
    //free transaction arrays

    for (int i = 0; i < block->transaction_num; i++){
        free(&block->txs[i]);
    }
    free(block->txs);

    //free struct
    free(block);
}