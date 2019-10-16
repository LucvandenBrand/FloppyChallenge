#include <game/item.h>

Item init_item(const char * name, const char * description)
{
    Item item = {name, description};
    return item;
}