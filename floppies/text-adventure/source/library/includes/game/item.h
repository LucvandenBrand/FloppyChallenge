#ifndef ITEM_H
#define ITEM_H

#define ID_NO_ITEM -1

typedef int ItemID;

typedef struct {
    char * name;
    char * description;
} Item;

Item init_item(char * name, char * description);
void free_item(Item * item);

#endif