#include "util/constants.h"
#include "transaction.h"
#include "wallet.h"
#include "crypto/secp256k1/src/secp256k1.c"
#include <time.h>
#include <stdio.h>


//creates wallet
void init_wallet(Wallet * wallet){
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);

    //bytearrays for keys
    unsigned char privkey[PRIVATE_KEY_LENGTH];
    unsigned char pubkey[PUBLIC_KEY_LENGTH];
    size_t pkl = sizeof(pubkey);

    //wrapper struct
    secp256k1_pubkey pubkeyObj;

    //seed random with time
    srand(time(NULL));

    //generate privkey
    for (int i = 0; i < PRIVATE_KEY_LENGTH; i++){
        privkey[i] = rand() % 256;
    }

    //generate pubkey from privkey
    int res = secp256k1_ec_pubkey_create(ctx, &pubkeyObj, privkey);

    if (!res){
        printf("Wallet creation failed due to pubkey creation failure");
    }
    //convert pubkey into bytearray
    secp256k1_ec_pubkey_serialize(ctx, pubkey, &pkl, &pubkeyObj, SECP256K1_EC_COMPRESSED);

    //init wallet by copying over
    wallet->created = (int)time(NULL);
    memcpy(wallet->pubkey, pubkey, PUBLIC_KEY_LENGTH);
    memcpy(wallet->privkey, privkey, PRIVATE_KEY_LENGTH); 
}


//sign hash of transaction
void sign_transaction(Wallet * wallet, Transaction * tx){ 
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);
    secp256k1_ecdsa_signature sig;
    unsigned char signature[SIGNATURE_LENGTH];

    //sign transaction hash
    int res = secp256k1_ecdsa_sign(ctx, &sig, tx->hash, wallet->privkey, NULL, NULL);

    if (!res){
        printf("Signature failed\n");

        return;
    }
    
    //convert signature into 64 byte bytearray
    secp256k1_ecdsa_signature_serialize_compact(ctx, signature, &sig);
    
    memcpy(tx->signature, signature, SIGNATURE_LENGTH);
}


//returns 1 if verification is correct, 0 otherwise
int verify_transaction_signature(Transaction * tx, unsigned char * sender_pubkey){
    int is_signature_valid;

    secp256k1_ecdsa_signature sig;
    secp256k1_pubkey pkey;
    secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_NONE);

    //parse the signature
    secp256k1_ecdsa_signature_parse_compact(ctx, &sig, tx->signature);

    //parse the public key
    int parse_res = secp256k1_ec_pubkey_parse(ctx, &pkey, sender_pubkey, PUBLIC_KEY_LENGTH);

    if(!parse_res){
        printf("Parsing public key failed");
        
        return 0;
    }

    is_signature_valid = secp256k1_ecdsa_verify(ctx, &sig, tx->hash, &pkey);

    return is_signature_valid;
}

