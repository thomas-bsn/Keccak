#include "keccak.h"
#include <stdlib.h>
#include <string.h>

void keccak(const char *filename, uint8_t *hash) 
{
    // 1. Diviser le fichier en blocs
    uint8_t *blocks;
    size_t num_blocks = bloc_part(filename, &blocks);

    // 2. Initialiser l'état
    uint64_t state[KECCAK_STATE_SIZE] = {0}; // Tableau de 25 entiers de 64 bits, initialisé à zéro

    // 3. Absorber les blocs dans l'état
    absorption(blocks, num_blocks, state);

    // 4. Squeeze pour extraire le hash final
    squeeze(state, hash, SHA3_256_HASH_SIZE);

    // Libérer la mémoire des blocs
    free(blocks);
}
