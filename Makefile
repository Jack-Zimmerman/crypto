main:
	gcc -o main main.c src/crypto/secp256k1/src/precomputed_ecmult.c src/crypto/secp256k1/src/precomputed_ecmult_gen.c

clean:
	del *.exe