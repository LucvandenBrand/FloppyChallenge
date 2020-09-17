#ifndef FILES_H
#define FILES_H

#include <stdbool.h>

long get_file_size(const char * file_path);
bool try_load_file(const char * file_path, char * buffer, long buffer_size);
bool try_write_file(const char * file_path, const char * buffer, long buffer_size);

#endif