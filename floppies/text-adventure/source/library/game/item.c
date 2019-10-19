#include <game/item.h>
#include <stdlib.h>

Item init_item(char * name, char * description)
{
    Item item = {name, description};
    return item;
}

void free_item(Item * item)
{
    free(item->name);
    free(item->description);
}