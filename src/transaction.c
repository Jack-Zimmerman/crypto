#include "crypto/hash.c"
#include <stdlib.h>
#include "transaction.h"
#include "util/constants.h"
#include <time.h>

//create transaction with needed values
void init_transaction(Transaction * tx, unsigned char * sender, unsigned char * recipient, unsigned long long int quantity) {

    //copy sender and recipient into tx
    memcpy(&tx->sender, sender, PUBLIC_KEY_LENGTH);
    memcpy(&tx->recipient, recipient, PUBLIC_KEY_LENGTH);

    //add quantities
    tx->amount = quantity;
    tx->timestamp = (int)time(NULL);

    //generate hash input string
    //hash is recipient, reciever, timestamp, amount sent 
    int input_size = (PUBLIC_KEY_LENGTH * 2) + sizeof(int) + sizeof(long int);
    unsigned char hash_input_buff[(PUBLIC_KEY_LENGTH * 2) + sizeof(int) + sizeof(long int)];
    unsigned char * hash;
    
    //place quantities into buff
    memcpy(hash_input_buff, sender, PUBLIC_KEY_LENGTH);
    memcpy(hash_input_buff + PUBLIC_KEY_LENGTH, recipient, PUBLIC_KEY_LENGTH);
    memcpy(hash_input_buff + (2 * PUBLIC_KEY_LENGTH), &tx->timestamp, sizeof(int));
    memcpy(hash_input_buff + (2 * PUBLIC_KEY_LENGTH) + sizeof(int), &tx->amount, sizeof(long int));
    
    hash = sha256_str(hash_input_buff, input_size);

    memcpy(tx->hash, hash, HASH_SIZE);

    free(hash);
}

