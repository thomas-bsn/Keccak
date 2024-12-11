#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "utils.h"
#include "keccak.h"

size_t read_file(const char *filename, uint8_t **buffer_out) 
{
    FILE *file = fopen(filename, "rb");
    if (!file) 
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    size_t filesize = ftell(file);
    rewind(file);

    *buffer_out = malloc(filesize);
    if (!*buffer_out) 
    {
        perror("Erreur d'allocation mémoire");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(*buffer_out, 1, filesize, file);
    if (bytes_read != filesize) 
    {
        perror("Erreur lors de la lecture du fichier");
        free(*buffer_out);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    return filesize;
}

void save_block_to_file(const char *filename, uint64_t *block, size_t block_size) 
{
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    for (size_t i = 0; i < block_size; i++) {
        fprintf(file, "%016lx\n", block[i]);
    }

    fclose(file);
    printf("Bloc enregistré dans %s\n", filename);
}


void test_squeeze() 
{
    uint64_t state[KECCAK_STATE_SIZE] = {0}; // 1600 bits (25 x 64 bits)

    uint8_t hash[SHA3_256_HASH_SIZE] = {0}; // 32 octets

    squeeze(state, hash, SHA3_256_HASH_SIZE);

    printf("Hash généré (squeeze uniquement) :\n");
    for (size_t i = 0; i < SHA3_256_HASH_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}


void print_hash(const uint8_t *hash, size_t hash_size) 
{
    for (size_t i = 0; i < hash_size; i++)
        printf("%02x", hash[i]);
    printf("\n");
}
