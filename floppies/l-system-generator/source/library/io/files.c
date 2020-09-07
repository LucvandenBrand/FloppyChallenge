#include <io/files.h>
#include <stdio.h>

long get_file_size(const char * file_path)
{
    char * buffer = 0;
    long length;
    FILE * file_handle = fopen (file_path, "rb");
    if (!file_handle)
        return -1;

    fseek (file_handle, 0L, SEEK_END);
    long size = ftell(file_handle);
    fclose (file_handle);
    return size;
}

bool try_load_file(const char * file_path, char * buffer, long buffer_size)
{
    FILE * file_handle = fopen (file_path, "rb");
    if (!file_handle)
        return false;
    unsigned long actually_read = fread(buffer, sizeof(char), buffer_size, file_handle);
    if (actually_read != buffer_size)
        return false;
    buffer[actually_read-1] = '\0';
    return fclose (file_handle) == 0;
}

bool try_write_file(const char * file_path, const char * buffer, long buffer_size)
{
    FILE * file_handle = fopen (file_path, "wb");
    if (!file_handle)
        return false;
    unsigned long actually_wrote = fwrite(buffer, sizeof(char), buffer_size, file_handle);
    if (actually_wrote != buffer_size)
        return false;
    return fclose (file_handle) == 0;
}