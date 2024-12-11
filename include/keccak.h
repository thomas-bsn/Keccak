#ifndef KECCAK_H
#define KECCAK_H

#include <stdint.h>
#include <stddef.h>

#define SHA3_256_HASH_SIZE 32  // 256 bits = 32 octets
#define KECCAK_STATE_SIZE 25   // 1600 bits / 64 bits = 25
#define KECCAK_RATE 136        // 1088 bits = 136 octets

static const uint64_t RC[24] = {
    0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808aULL, 
    0x8000000080008000ULL, 0x000000000000808bULL, 0x0000000080000001ULL, 
    0x8000000080008081ULL, 0x8000000000008009ULL, 0x000000000000008aULL, 
    0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000aULL, 
    0x000000008000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL, 
    0x8000000000008003ULL, 0x8000000000008002ULL, 0x8000000000000080ULL, 
    0x000000000000800aULL, 0x800000008000000aULL, 0x8000000080008081ULL, 
    0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL
};

void keccak(const char *filename, uint8_t *hash);

size_t bloc_part(const char *filename, uint8_t **blocks_out);
void absorption(uint8_t *blocks, size_t num_blocks, uint64_t state[KECCAK_STATE_SIZE]);
void permut(uint64_t state[KECCAK_STATE_SIZE]);
void squeeze(uint64_t state[KECCAK_STATE_SIZE], uint8_t *hash, size_t hash_size);

#endif // KECCAK_H
