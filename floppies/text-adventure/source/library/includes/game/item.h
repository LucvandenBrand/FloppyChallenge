#ifndef ITEM_H
#define ITEM_H

#include <id/id.h>

#define ID_NO_ITEM ID_EMPTY

typedef ID ItemID;

typedef struct {
    char * name;
    char * description;
} Item;

Item init_item(char * name, char * description);
void free_item(Item * item);

#endif