#ifndef BINARY_BLOB_H
#define BINARY_BLOB_H

#include <stdint.h>

typedef struct {
    uint8_t * data;
    int num_bytes;
} BinaryBlob;

BinaryBlob malloc_binary_blob(int num_bytes);
void free_binary_blob(BinaryBlob * blob);

#endif