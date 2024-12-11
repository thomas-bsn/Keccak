#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "keccak.h"

void squeeze(uint64_t state[KECCAK_STATE_SIZE], uint8_t *hash, size_t hash_size) 
{
    printf("Squeeze loading...\n");
    size_t rate_bytes = KECCAK_RATE / 8;
    size_t bytes_extracted = 0;

    while (bytes_extracted < hash_size) {
        size_t to_copy = (hash_size - bytes_extracted < rate_bytes) 
                         ? hash_size - bytes_extracted 
                         : rate_bytes;

        memcpy(hash + bytes_extracted, state, to_copy);

        bytes_extracted += to_copy;

        if (bytes_extracted < hash_size) 
            permut(state);
    }
    printf("Squeeze loaded\n");
}
