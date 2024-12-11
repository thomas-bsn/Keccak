#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keccak.h"
#include "utils.h"

size_t bloc_part(const char *filename, uint8_t **blocks_out) {
    printf("Bloc part loading...\n");

    uint8_t *file_content;
    size_t filesize = read_file(filename, &file_content);

    size_t block_size = KECCAK_RATE; // 1088 bits = 136 octets
    size_t num_blocks = (filesize + block_size - 1) / block_size;

    *blocks_out = malloc(num_blocks * block_size);
    if (!*blocks_out) {
        perror("Erreur d'allocation mémoire");
        free(file_content);
        exit(EXIT_FAILURE);
    }
    memset(*blocks_out, 0, num_blocks * block_size);

    memcpy(*blocks_out, file_content, filesize);

    (*blocks_out)[filesize] = 0x06; // Bit 1 suivi de 0
    (*blocks_out)[num_blocks * block_size - 1] |= 0x80; // Dernier bit du dernier bloc = 1

    free(file_content);

    printf("Bloc part loaded\n");
    return num_blocks;
}
