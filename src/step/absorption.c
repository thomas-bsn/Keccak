#include <stdint.h>
#include <stdio.h>
#include "keccak.h"

void absorption(uint8_t *blocks, size_t num_blocks, uint64_t state[KECCAK_STATE_SIZE]) 
{
    printf("Absorption loading...\n");
    size_t rate = KECCAK_RATE / 8; 

    for (size_t i = 0; i < num_blocks; i++) 
    {
        for (size_t j = 0; j < rate / 8; j++) 
            state[j] ^= ((uint64_t *)blocks)[i * (rate / 8) + j];
        permut(state);
    }
    printf("Absorption loaded\n");
}
