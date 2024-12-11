#include <stdint.h>
#include <stdio.h>
#include "keccak.h"
#include "utils.h"

void absorption(uint8_t *blocks, size_t num_blocks, uint64_t state[KECCAK_STATE_SIZE]) 
{
    printf("Absorption loading...\n");
    size_t rate = KECCAK_RATE / 8;

    for (size_t i = 0; i < num_blocks; i++) 
    {
        for (size_t j = 0; j < rate; j++) 
            state[j] ^= ((uint64_t *)blocks)[i * rate + j];

        if (i == 0)
        {
            printf("Taille du bloc extrait (C) : %zu entiers de 64 bits\n", rate);
            save_block_to_file("test/first_block.txt", &((uint64_t *)blocks)[i * rate], rate);
        }
        permut(state);
    }
    printf("Absorption loaded\n");
}

