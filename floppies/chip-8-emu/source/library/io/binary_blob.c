#include <io/binary_blob.h>
#include <stdlib.h>

BinaryBlob malloc_binary_blob(int num_bytes)
{
    if (num_bytes < 0) {
        BinaryBlob empty_blob = {NULL, -1};
        return empty_blob;
    }

    uint8_t * data = malloc(sizeof(uint8_t) * num_bytes);
    BinaryBlob blob = {data, num_bytes};
    return blob;
}

void free_binary_blob(BinaryBlob * blob)
{
    free(blob->data);
    blob->data = NULL;
    blob->num_bytes = -1;
}