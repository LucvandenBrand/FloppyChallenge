#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
#include <stdbool.h>
#include <list/id_list.h>

typedef struct {
    IDList item_id_list;
} Player;

Player init_player();
void free_player(Player * player);
void add_item_to_player(Player * player, ItemID item_id);
void remove_item_from_player(Player * player, ItemID item_id);
bool player_has_item(Player player, ItemID item_id);

#endif