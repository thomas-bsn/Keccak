#include "keccak.h"
#include <string.h>
#include <stdio.h>

// Sous-étape Theta
void Theta(uint64_t state[KECCAK_STATE_SIZE]) 
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

// Sous-étape Rho
void Rho(uint64_t state[KECCAK_STATE_SIZE]) {
    static const int RHO_OFFSETS[5][5] = 
    {
        { 0, 36, 3, 41, 18 },
        { 1, 44, 10, 45, 2 },
        { 62, 6, 43, 15, 61 },
        { 28, 55, 25, 21, 56 },
        { 27, 20, 39, 8, 14 }
    };

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

// Sous-étape Pi
void Pi(uint64_t state[KECCAK_STATE_SIZE]) 
{
    uint64_t temp[KECCAK_STATE_SIZE];
    memcpy(temp, state, KECCAK_STATE_SIZE * sizeof(uint64_t));

    for (int x = 0; x < 5; x++) 
        for (int y = 0; y < 5; y++) 
            state[y + 5 * ((2 * x + 3 * y) % 5)] = temp[x + 5 * y];
}

// Sous-étape Chi
void Chi(uint64_t state[KECCAK_STATE_SIZE]) 
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

// Sous-étape Iota
void Iota(uint64_t state[KECCAK_STATE_SIZE], uint64_t round_constant) 
{
    state[0] ^= round_constant;
}

// Fonction principale Permut
void permut(uint64_t state[KECCAK_STATE_SIZE]) 
{
    for (int round = 0; round < 24; round++) 
    {
        Theta(state);
        Rho(state);
        Pi(state);
        Chi(state);
        Iota(state, RC[round]);
    }
}
