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

    for (int i = 0; i < 10000; i++){
        init_transaction(&tx, sender.pubkey, reciever.pubkey, 1000);
        sign_transaction(&sender, &tx);

        Block blk;

        init_block(&blk, &sender, 10000000, i);
        add_transaction_to_block(&blk, &tx);
        complete_block(&blk);

        int res = write_block_to_file(&blk, "test.dat");
    }

    Block * blks = read_blocks_from_file("test.dat", 10000);

    for (int a = 0; a < 10000; a++){
        printf("%d ",blks[a].height);
        for (int i = 0; i < HASH_SIZE; i++){
            printf("%x", blks[a].hash[i]);
        }
        printf("\n");
    }
}



