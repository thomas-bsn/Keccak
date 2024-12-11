#include <stdio.h>
#include <stdlib.h>
#include "keccak.h"
#include "utils.h"

int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    uint8_t hash[SHA3_256_HASH_SIZE];

    keccak(filename, hash);

    printf("SHA3-256 hash of '%s':\n", filename);
    print_hash(hash, SHA3_256_HASH_SIZE);

    return EXIT_SUCCESS;
}
