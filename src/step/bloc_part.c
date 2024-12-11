#include "keccak.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apply_padding(uint8_t *blocks, size_t filesize, size_t block_size, size_t num_blocks) 
{
    blocks[filesize] = 0x06; // On met le premier bit à 1 et le reste à 0
    blocks[num_blocks * block_size - 1] |= 0x80; // On met le dernier bit à 1
}

size_t bloc_part(const char *filename, uint8_t **blocks_out) 
{
    printf("==== Bloc part loading... ====\n");

    uint8_t *file_content;
    size_t filesize = read_file(filename, &file_content);

    size_t block_size = KECCAK_RATE;
    size_t num_blocks = (filesize + block_size - 1) / block_size;

    *blocks_out = malloc(num_blocks * block_size);
    if (!*blocks_out) 
    {
        perror("Erreur d'allocation mémoire");
        free(file_content);
        exit(EXIT_FAILURE);
    }
    memset(*blocks_out, 0, num_blocks * block_size); // On remplit les blocs de zéros

    memcpy(*blocks_out, file_content, filesize);

    if (filesize % block_size != 0) 
    {
        apply_padding(*blocks_out, filesize, block_size, num_blocks);
    }

    free(file_content);


    printf("Taille du fichier : %zu octets\n", filesize);
    printf("Nombre de blocs calculés : %zu\n", num_blocks);

    printf("==== Bloc part loaded ====\n\n");
    return num_blocks;
}
