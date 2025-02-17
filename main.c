#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "src/transaction.c"
#include "src/wallet.c"

int main(void){
    Wallet sender;
    Wallet reciever;
    Transaction tx;

    init_wallet(&sender); 
    init_wallet(&reciever);

    init_transaction(&tx, sender.pubkey, reciever.pubkey, 1000);
    sign_transaction(&sender, &tx);

    int res = verify_transaction_signature(&tx, sender.pubkey);
}

