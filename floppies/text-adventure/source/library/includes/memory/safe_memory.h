#ifndef SAFE_MEMORY_H
#define SAFE_MEMORY_H

void * safe_malloc(unsigned size);
void * safe_realloc(void * old_ptr, unsigned new_size);

#endif
