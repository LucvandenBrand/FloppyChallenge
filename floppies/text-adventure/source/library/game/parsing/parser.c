#include <game/parsing/parser.h>
#include <stdlib.h>
#include <string.h>
#include <io/text_interface.h>
#include <game/text_generator.h>
#include <memory/safe_memory.h>
#include <string/string_ops.h>

void apply_input_to_game_state(const char * input, GameState * game)
{
    TokenList token_list = text_to_tokens(input, *game);
    apply_tokens_to_game_state(token_list, game);
    free_tokens(&token_list);
}

TokenList text_to_tokens(const char * input, GameState game)
{
    TokenList tokens = {NULL, 0};
    int max_num_tokens = 2;
    tokens.tokens = safe_malloc(max_num_tokens * sizeof(Token));

    unsigned long num_chars = strlen(input);
    char * lower_input = safe_malloc(num_chars * sizeof(char));
    strncpy(lower_input, input, num_chars);
    string_to_lowercase(lower_input, num_chars);

    unsigned long start = 0, end = 1;
    while (end <= num_chars)
    {
        if (*(lower_input + start) == ' ')
        {
            start = end;
            end++;
            continue;
        }

        char * sub_string = strndup(lower_input + start, end - start);
        Token token = match_token(sub_string, game);
        free(sub_string);
        if (token.type != NONE)
        {
            if (tokens.length >= max_num_tokens)
            {
                max_num_tokens *= 2;
                tokens.tokens = safe_realloc(tokens.tokens, max_num_tokens * sizeof(Token));
            }
            tokens.tokens[tokens.length++] = token;
            start = end;
        }
        end++;
    }

    tokens.tokens = safe_realloc(tokens.tokens, tokens.length * sizeof(Token));

    free(lower_input);
    return tokens;
}

void apply_tokens_to_game_state(TokenList token_list, GameState * game)
{
    unsigned token_index = 0;
    if (accept_token(token_list, &token_index, EXIT))
    {
        put_text("You smash your head against a wall, the sweet mercy of death embraces you.\n");
        game->is_running = false;
        return;
    }

    if (accept_action(token_list, &token_index, game) || accept_movement(token_list, &token_index, game))
        return;

    put_text("Sorry, I do not understand that command.\n");
}

bool accept_action(TokenList token_list, unsigned * token_index, GameState * game)
{
    if (accept_inspecting(token_list, token_index, game) || accept_taking(token_list, token_index, game) ||
        accept_placing(token_list, token_index, game) || accept_locking(token_list, token_index, game) ||
        accept_unlocking(token_list, token_index, game) || accept_killing(token_list, token_index, game))
        return true;
    return false;
}

bool accept_inspecting(TokenList token_list, unsigned * token_index, GameState * game)
{
    if (!accept_token(token_list, token_index, LOOK))
        return false;

    if (!accept_token(token_list, token_index, AT))
    {
        put_text("You stared into nothing for a few seconds.\n");
        return true;
    }

    if (accept_token(token_list, token_index, ROOM))
        describe_room(*game, game->current_room);
    else if (accept_token(token_list, token_index, INVENTORY))
        list_items(*game, game->player.item_id_list);
    else if (accept_token(token_list, token_index, ITEM))
    {
        ItemID item_id = token_list.tokens[*token_index-1].value;
        if (is_item_in_room(game->rooms[game->current_room], item_id) || player_has_item(game->player, item_id))
        {
            Item item = game->items[item_id];
            put_text("%s\n", item.description);
        }
        else
        {
            put_text("That item is not in your inventory nor in the room.\n");
        }
    }
    else
        put_text("You try to look for it, but you cannot find it.\n");
    return true;

}

bool accept_taking(TokenList token_list, unsigned * token_index, GameState * game)
{
    if (accept_token(token_list, token_index, TAKE))
    {
        if (accept_token(token_list, token_index, ITEM))
        {
            ItemID item_id = token_list.tokens[*token_index-1].value;
            if (is_item_in_room(game->rooms[game->current_room], item_id))
            {
                Item item = game->items[item_id];
                put_text("You pick up the %s and put it in your pocket.\n", item.name);
                add_item_to_player(&game->player, item_id);
                remove_item_from_room(&game->rooms[game->current_room], item_id);
                return true;
            }
        }

        put_text("You grasp in thin air... that item is not in the room.\n");
        return true;
    }
    return false;
}

bool accept_placing(TokenList token_list, unsigned * token_index, GameState * game)
{
    if (accept_token(token_list, token_index, PLACE))
    {
        if (accept_token(token_list, token_index, ITEM))
        {
            ItemID item_id = token_list.tokens[*token_index-1].value;
            if (player_has_item(game->player, item_id))
            {
                Item item = game->items[item_id];
                put_text("You take the %s and place it in the room.\n", item.name);
                remove_item_from_player(&game->player, item_id);
                add_item_to_room(&game->rooms[game->current_room], item_id);
                return true;
            }
        }
        put_text("You fumble in your pockets... that item is not in your possession.\n");
        return true;
    }
    return false;
}

bool accept_locking(TokenList token_list, unsigned * token_index, GameState * game) {
    if (!accept_token(token_list, token_index, LOCK))
        return false;
    if (!accept_token(token_list, token_index, DOOR))
    {
        put_text("Please name a door in this room.\n");
        return true;
    }

    ID doorID = token_list.tokens[*token_index - 1].value;
    Door * door = &game->rooms[game->current_room].doors.doors[doorID];
    if (!accept_token(token_list, token_index, WITH)) {
        put_text("Lock the %s with what item?\n", door->name);
        return true;
    }
    if (!accept_token(token_list, token_index, ITEM))
    {
        put_text("Please name an item in your inventory.\n");
        return true;
    }

    ItemID item_id = token_list.tokens[*token_index-1].value;
    if (!player_has_item(game->player, item_id))
    {
        put_text("You do not have that in your inventory.\n");
    }
    else if (is_door_locked(*door))
    {
        put_text("The door is already locked, but it's good to make sure.\n");
    }
    else if(try_lock_door(door, item_id))
    {
        put_text("You locked the door.\n");
    }
    else
    {
        put_text("You cannot lock this door with that item.\n");
    }

    return true;
}

bool accept_unlocking(TokenList token_list, unsigned * token_index, GameState * game)
{
    if (!accept_token(token_list, token_index, UNLOCK))
        return false;
    if (!accept_token(token_list, token_index, DOOR))
    {
        put_text("Please name a door in this room.\n");
        return true;
    }

    ID doorID = token_list.tokens[*token_index - 1].value;
    Door * door = &game->rooms[game->current_room].doors.doors[doorID];
    if (!accept_token(token_list, token_index, WITH)) {
        put_text("Unlock the %s with what item?\n", door->name);
        return true;
    }
    if (!accept_token(token_list, token_index, ITEM))
    {
        put_text("Please name an item in your inventory.\n");
        return true;
    }

    ItemID item_id = token_list.tokens[*token_index-1].value;
    if (!player_has_item(game->player, item_id))
    {
        put_text("You do not have that in your inventory.\n");
    }
    else if (!is_door_locked(*door))
    {
        put_text("The door moves as you try to unlock it, it's already open!\n");
    }
    else if(try_unlock_door(door, item_id))
    {
        put_text("You unlocked the door.\n");
    }
    else
    {
        put_text("You cannot unlock this door with that item.\n");
    }

    return true;
}

bool accept_killing(TokenList token_list, unsigned * token_index, GameState * game)
{
    if (!accept_token(token_list, token_index, KILL))
        return false;
    if (!accept_token(token_list, token_index, ENTITY))
    {
        put_text("You could not kill what is not there, but you imagined it.\n");
        return true;
    }

    EntityID entity_id = token_list.tokens[*token_index - 1].value;
    Entity entity = game->entities[entity_id];
    if (!is_entity_in_room(game->rooms[game->current_room], entity_id))
    {
        put_text("The %s is not in this room.\n", entity.name);
        return true;
    }

    if (!accept_token(token_list, token_index, WITH))
    {
        put_text("Kill the %s with what item?\n", entity.name);
        return true;
    }
    if (!accept_token(token_list, token_index, ITEM))
    {
        put_text("Please name an item in your inventory.\n");
        return true;
    }

    ItemID item_id = token_list.tokens[*token_index-1].value;
    if (!player_has_item(game->player, item_id))
    {
        put_text("You do not have that in your inventory.\n");
    }
    else if (entity.vulnerability != item_id)
    {
        Item item = game->items[item_id];
        put_text("You try to kill the %s with the %s, but nothing happens...\n", entity.name, item.name);
    }
    else
    {
        put_text("%s\n", entity.die);
        remove_entity_from_room(&game->rooms[game->current_room], entity_id);
        ItemID dropped_item_id = entity.holding_item;
        if (dropped_item_id != ID_NO_ITEM)
        {
            add_item_to_room(&game->rooms[game->current_room], dropped_item_id);
            Item dropped_item = game->items[dropped_item_id];
            put_text("The %s dropped ", entity.name);
            choose_indefinite_article(dropped_item.name);
            put_text(" %s.\n", dropped_item.name);
        }
    }

    return true;
}

bool accept_movement(TokenList token_list, unsigned * token_index, GameState * game)
{
    if (accept_token(token_list, token_index, WALK) && accept_token(token_list, token_index, DIRECTION))
    {
        Direction door_direction = token_list.tokens[*token_index-1].value;
        if (!room_has_door_in_direction(game->rooms[game->current_room], door_direction))
        {
            put_text("BONK!\nYou just bumped into a wall...\n");
            return true;
        }
        ID doorID = get_room_door_id_with_direction(game->rooms[game->current_room], door_direction);
        Door door = game->rooms[game->current_room].doors.doors[doorID];
        if (is_door_locked(door))
        {
            put_text("The %s is locked.\n", door.name);
            return true;
        }
        if (is_exit_door(door))
        {
            put_text("%s\n", game->win_text);
            game->is_running = false;
            return true;
        }
        game->current_room = door.roomId; // TODO : implement keys.
        return true;
    }
    return false;
}

bool accept_token(TokenList token_list, unsigned * token_index, TokenType expected)
{
    if (*token_index < token_list.length && token_list.tokens[*token_index].type == expected)
    {
        (*token_index)++;
        return true;
    }
    return false;
}

void free_tokens(TokenList * token_list)
{
    free(token_list->tokens);
    token_list->tokens = NULL;
    token_list->length = 0;
}