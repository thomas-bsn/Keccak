#include "keccak.h"
#include <string.h>
#include <stdio.h>

void theta(uint64_t state[KECCAK_STATE_SIZE]) 
{
    uint64_t C[5], D[5];

    for (int x = 0; x < 5; x++) 
        C[x] = state[x] ^ state[x + 5] ^ state[x + 10] ^ state[x + 15] ^ state[x + 20];

    for (int x = 0; x < 5; x++) 
    {
        D[x] = C[(x + 4) % 5] ^ ((C[(x + 1) % 5] << 1) | (C[(x + 1) % 5] >> (64 - 1)));
        for (int y = 0; y < 5; y++) 
            state[x + 5 * y] ^= D[x];
    }
}

void rho(uint64_t state[KECCAK_STATE_SIZE]) 
{
    for (int x = 0; x < 5; x++) 
    {
        for (int y = 0; y < 5; y++) 
        {
            int idx = x + 5 * y;
            state[idx] = (state[idx] << RHO_OFFSETS[x][y]) | 
                         (state[idx] >> (64 - RHO_OFFSETS[x][y]));
        }
    }
}

void pi(uint64_t state[KECCAK_STATE_SIZE]) 
{
    uint64_t temp[KECCAK_STATE_SIZE];
    memcpy(temp, state, KECCAK_STATE_SIZE * sizeof(uint64_t));

    for (int x = 0; x < 5; x++) 
        for (int y = 0; y < 5; y++) 
            state[y + 5 * ((2 * x + 3 * y) % 5)] = temp[x + 5 * y];
}

void chi(uint64_t state[KECCAK_STATE_SIZE]) 
{
    uint64_t temp[5];

    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            temp[x] = state[x + 5 * y];
        }
        for (int x = 0; x < 5; x++) {
            state[x + 5 * y] ^= (~temp[(x + 1) % 5]) & temp[(x + 2) % 5];
        }
    }
}

void iota(uint64_t state[KECCAK_STATE_SIZE], uint64_t round_constant) 
{
    state[0] ^= round_constant;
}

void print_state(const uint64_t state[KECCAK_STATE_SIZE], const char *stage, int round) 
{
    printf("\nÉtat après %s (Tour %d) :\n", stage, round);
    for (int y = 0; y < 5; y++) 
    {
        for (int x = 0; x < 5; x++) 
        {
            printf("%016lx ", state[x + 5 * y]);
        }
        printf("\n");
    }
}

void permut(uint64_t state[KECCAK_STATE_SIZE]) 
{
    for (int round = 0; round < 24; round++) 
    {
        // printf("\n=== Début du tour %d ===\n", round);
        // print_state(state, "Initialisation", round);

        theta(state);
        // print_state(state, "Theta", round);

        rho(state);
        // print_state(state, "Rho", round);

        pi(state);
        // print_state(state, "Pi", round);

        chi(state);
        // print_state(state, "Chi", round);

        iota(state, RC[round]);
        // print_state(state, "Iota", round);
    }
}
