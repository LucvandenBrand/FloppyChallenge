#include <stdlib.h>
#include <io/text_interface.h>

void * safe_malloc(unsigned size)
{
    if (size == 0)
        return NULL;

    void * ptr = malloc(size);
    if (ptr == NULL)
    {
        put_color_text(RED, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void * safe_realloc(void * old_ptr, unsigned new_size)
{
    if (new_size == 0)
    {
        free(old_ptr);
        return NULL;
    }

    void * new_ptr = realloc(old_ptr, new_size);
    if (new_ptr == NULL)
    {
        free(old_ptr);
        put_color_text(RED, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    return new_ptr;
}