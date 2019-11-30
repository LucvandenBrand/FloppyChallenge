#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include "item.h"

typedef struct {
    char * name;
    char * description;
    char * attack;
    char * die;
    int kill_count;
    int start_kill_count;
    ItemID holding_item;
    ItemID vulnerability;
} Entity;

typedef ID EntityID;

#define ID_NO_ENTITY ID_EMPTY

Entity init_entity(char * name, char * description, char * attack, char * die, int kill_count, ItemID holding_item,
                   ItemID vulnerability);
void free_entity(Entity * entity);

#endif