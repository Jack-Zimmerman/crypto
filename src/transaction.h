#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "util/constants.h"

#define HASH_SIZE 32

typedef struct Transaction {
    unsigned char hash[HASH_SIZE];
    unsigned char sender[PUBLIC_KEY_LENGTH];
    unsigned char recipient[PUBLIC_KEY_LENGTH];
    unsigned char signature[SIGNATURE_LENGTH];
    unsigned long long int amount;
    int timestamp; 
} Transaction;

void init_transaction(Transaction *, unsigned char *, unsigned char *, unsigned long long int);


#endif