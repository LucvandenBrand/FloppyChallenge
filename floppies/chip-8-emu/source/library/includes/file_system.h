#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <binary_blob.h>

char * get_full_path(const char * file_name, char * full_path);
int file_path_exists(const char * file_path);
BinaryBlob * read_binary_file(const char * file_path, BinaryBlob * blob);
int get_file_size(const char * file_path);

#endif