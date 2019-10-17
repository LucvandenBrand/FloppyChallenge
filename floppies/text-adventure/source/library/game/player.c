#include <game/player.h>
#include <stdlib.h>
#include <string.h>

Player init_player()
{
    Player player;
    player.num_items = 0;
    player.max_items = 4;
    player.items = malloc(player.max_items * sizeof(ItemID));
    return player;
}

void free_player(Player * player)
{
    free(player->items);
    player->items = NULL;
    player->num_items = 0;
    player->max_items = 0;
}

void add_item_to_player(Player * player, ItemID item_id)
{
    if (player->num_items+1 >= player->max_items)
    {
        player->max_items *= 2;
        player->items = realloc(player->items, player->max_items * sizeof(ItemID));
    }
    player->items[player->num_items++] = item_id;
}

void remove_item_from_player(Player * player, ItemID item_id)
{
    for (unsigned item_index = 0; item_index < player->num_items; item_index++)
    {
        if (player->items[item_index] == item_id)
        {
            player->num_items--;
            for (unsigned shift_index = item_index; shift_index < player->num_items; shift_index++)
            {
                player->items[shift_index] = player->items[shift_index + 1];
            }
            break;
        }
    }
}