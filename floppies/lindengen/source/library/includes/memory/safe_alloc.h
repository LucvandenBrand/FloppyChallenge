#ifndef SAFE_ALLOC_H
#define SAFE_ALLOC_H

#include "stdlib.h"

void * safe_malloc(size_t size);
void * safe_realloc(void * ptr, size_t size);

#endif
