#include <io/binary_blob.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <io/file_system.h>
#include <io/cmd_interface.h>

char * get_full_path(const char * file_name, char * full_path)
{
    return realpath(file_name, full_path);
}

int file_path_exists(const char * file_path)
{
    return access(file_path, F_OK ) != -1;
}

BinaryBlob * read_binary_file(const char * file_path, BinaryBlob * blob)
{
    FILE *file_pointer = fopen(file_path, "rb");
    if (file_pointer == NULL)
    {
        log_message(ERROR, "Could not read file %s.", file_path);
        exit(EXIT_FAILURE);
    }
    unsigned long bytes_read = fread(blob->data, blob->num_bytes, 1, file_pointer);
    fclose(file_pointer);
    return blob;
}

int get_file_size(const char * file_path)
{
    FILE *file_pointer = fopen(file_path, "rb");
    if (file_pointer == NULL)
        return -1;

    uint8_t byte;
    int num_bytes = 0;
    while(fread(&byte, sizeof(byte), 1, file_pointer))
        ++num_bytes;

    fclose(file_pointer);

    return num_bytes;
}