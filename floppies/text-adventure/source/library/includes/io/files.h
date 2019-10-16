#ifndef FILES_H
#define FILES_H

long get_file_size(const char * file_path);
void load_file(const char * file_path, char * buffer, long buffer_size);

#endif