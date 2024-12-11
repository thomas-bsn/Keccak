#include <stdio.h>
#include <stdlib.h>
#include "keccak.h"
#include "utils.h"

int main(int argc, char *argv[]) 
{
    if (TEST == 1) 
    {
        printf("Test squeeze avec un state initialisé à 0\n");
        test_squeeze();
        return 0;
    }

    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    uint8_t hash[SHA3_256_HASH_SIZE];

    keccak(filename, hash);

    printf("hash SHA3-256 de '%s':\n", filename);
    print_hash(hash, SHA3_256_HASH_SIZE);

    return 0;
}
