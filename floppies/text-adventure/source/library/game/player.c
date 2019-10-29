#include <game/player.h>
#include <stdlib.h>
#include <string.h>

Player init_player()
{
    Player player;
    player.item_id_list = init_list();
    return player;
}

void free_player(Player * player)
{
    free_list(&player->item_id_list);
}

void add_item_to_player(Player * player, ItemID item_id)
{
    add_id(&player->item_id_list, item_id);
}

void remove_item_from_player(Player * player, ItemID item_id)
{
    remove_id(&player->item_id_list, item_id);
}

bool player_has_item(Player player, ItemID item_id)
{
    return has_id(player.item_id_list, item_id);
}