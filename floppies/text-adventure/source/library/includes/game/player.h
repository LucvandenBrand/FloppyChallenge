#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"

typedef struct {
    Item * items;
    unsigned num_items;
    unsigned max_items;
} Player;

Player init_player();
void free_player(Player * player);
void add_item_to_player(Player * player, Item item);
void remove_item_from_player(Player * player, const char * item_name);

#endif