#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "src/transaction.c"
#include "src/wallet.c"
#include "src/block.c"

int main(void){
    Wallet sender;
    Wallet reciever;
    Transaction tx;
    

    init_wallet(&sender); 
    init_wallet(&reciever);

    init_transaction(&tx, sender.pubkey, reciever.pubkey, 1000);
    sign_transaction(&sender, &tx);

    Block blk;

    init_block(&blk, &sender, 10000000, 0);
    add_transaction_to_block(&blk, &tx);

    for (int i = 0; i < blk.transaction_num; i++)
    {
        printf("%d\n", blk.transactions[0]->amount);
    }
}

