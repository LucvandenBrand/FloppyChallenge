#include <game/parsing/token.h>
#include <string.h>
#include <game/direction.h>
#include <game/item.h>

Token match_token(const char * string, GameState game)
{
    Token token = {NONE, -1};
    ItemID item_id = get_item_id(string, game);
    if (item_id != ID_NO_ITEM)
    {
        token.type = ITEM;
        token.value = item_id;
    }
    else if (strcmp(string, "room") == 0)
        token.type = ROOM;
    else if (strcmp(string, "inventory") == 0)
        token.type = INVENTORY;
    else if (strcmp(string, "look") == 0)
        token.type = LOOK;
    else if (strcmp(string, "at") == 0)
        token.type = AT;
    else if (strcmp(string, "take") == 0)
        token.type = TAKE;
    else if (strcmp(string, "place") == 0)
        token.type = PLACE;
    else if (strcmp(string, "walk") == 0)
        token.type = WALK;
    else if (strcmp(string, "north") == 0)
    {
        token.type = DIRECTION;
        token.value = NORTH;
    }
    else if (strcmp(string, "east") == 0)
    {
        token.type = DIRECTION;
        token.value = EAST;
    }
    else if (strcmp(string, "south") == 0)
    {
        token.type = DIRECTION;
        token.value = SOUTH;
    }
    else if (strcmp(string, "west") == 0)
    {
        token.type = DIRECTION;
        token.value = WEST;
    }
    else if (strcmp(string, "exit") == 0)
    {
        token.type = EXIT;
    }

    return token;
}