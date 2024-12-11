#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>

size_t read_file(const char *filename, uint8_t **buffer_out);
void print_hash(const uint8_t *hash, size_t hash_size);
void save_block_to_file(const char *filename, uint64_t *block, size_t block_size); 
void test_squeeze();

#endif // UTILS_H
