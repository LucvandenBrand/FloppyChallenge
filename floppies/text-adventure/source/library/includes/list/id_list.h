#ifndef ID_LIST_H
#define ID_LIST_H

#include <stdbool.h>
#include <game/id.h>

typedef struct {
    ID * ids;
    int num_ids;
    int list_size;
} IDList;

IDList init_list();
void free_list(IDList * list);
void add_id(IDList * list, ID id);
void remove_id(IDList * list, ID id);
bool has_id(IDList list, ID id);

#endif