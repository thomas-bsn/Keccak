#include "keccak.h"
#include <stdlib.h>
#include <string.h>

void keccak(const char *filename, uint8_t *hash) 
{
    uint8_t *blocks;
    size_t num_blocks = bloc_part(filename, &blocks);

    uint64_t state[KECCAK_STATE_SIZE] = {0};

    absorption(blocks, num_blocks, state);

    squeeze(state, hash, SHA3_256_HASH_SIZE);

    free(blocks);
}
