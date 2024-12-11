#include "utils.h"
#include <stdlib.h>

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

void print_hash(const uint8_t *hash, size_t hash_size) 
{
    for (size_t i = 0; i < hash_size; i++)
        printf("%02x", hash[i]);
    printf("\n");
}
