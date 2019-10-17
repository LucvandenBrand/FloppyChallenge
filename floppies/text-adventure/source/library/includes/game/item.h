#ifndef ITEM_H
#define ITEM_H

#define ID_NO_ITEM -1;

typedef int ItemID;

typedef struct {
    const char * name;
    const char * description;
} Item;

Item init_item(const char * name, const char * description);

#endif