#ifndef WALLET_H
#define WALLET_H

#include "util/constants.h"
#include "transaction.h"

typedef struct Wallet {
    unsigned char pubkey[PUBLIC_KEY_LENGTH];
    unsigned char privkey[PRIVATE_KEY_LENGTH];
    int created;
} Wallet;


//function to create public and private keys
void init_wallet(Wallet *);

void sign_transaction(Wallet *, Transaction*);

int verify_transaction_signature(Transaction*, unsigned char *);


/*
//argument being target file
Wallet * freadTransaction(char *);

//argument being target file
Wallet * fwriteTransaction(char *);
*/

#endif