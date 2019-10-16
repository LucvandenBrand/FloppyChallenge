#ifndef ITEM_H
#define ITEM_H

typedef struct {
    const char * name;
    const char * description;
} Item;

Item init_item(const char * name, const char * description);

#endif