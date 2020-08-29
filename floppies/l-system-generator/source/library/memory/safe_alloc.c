#include "memory/safe_alloc.h"

void * safe_malloc(size_t size)
{
    void * ptr = malloc(size);
    if (ptr == NULL)
    {
        printf("ERROR - Could not allocate memory of size %d, exiting program.\n", size);
        exit(EXIT_FAILURE);
    }

    return ptr;
}

void * safe_realloc(void * ptr, size_t size)
{
    void * new_ptr = realloc(ptr, size);
    if (new_ptr == NULL)
    {
        printf("ERROR - Could not reallocate memory to size %d, exiting program.\n", size);
        exit(EXIT_FAILURE);
    }

    return new_ptr;
}