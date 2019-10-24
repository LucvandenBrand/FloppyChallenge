#include <game/parsing/parser.h>
#include <stdlib.h>
#include <string.h>
#include <io/text_interface.h>
#include <game/text_generator.h>

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
    tokens.tokens = malloc(max_num_tokens * sizeof(Token));
    unsigned long num_chars = strlen(input);
    unsigned long start = 0, end = 1;
    while (end <= num_chars)
    {
        if (*(input + start) == ' ')
        {
            start = end;
            end++;
            continue;
        }

        const char * sub_string = strndup(input + start, end - start);
        Token token = match_token(sub_string, game);
        if (token.type != NONE)
        {
            if (tokens.length >= max_num_tokens)
            {
                max_num_tokens *= 2;
                tokens.tokens = realloc(tokens.tokens, max_num_tokens * sizeof(Token));
            }
            tokens.tokens[tokens.length++] = token;
            start = end;
        }
        end++;
    }
    return tokens;
}

void apply_tokens_to_game_state(TokenList token_list, GameState * game)
{
    unsigned token_index = 0;
    if (accept_token(token_list, &token_index, EXIT))
    {
        game->is_running = false;
        return;;
    }

    if (accept_action(token_list, &token_index, game) || accept_movement(token_list, &token_index, game))
        return;

    put_text("Sorry, I do not understand that command.\n");
}

bool accept_action(TokenList token_list, unsigned * token_index, GameState * game)
{
    if (accept_inspecting(token_list, token_index, game) || accept_taking(token_list, token_index, game) ||
        accept_placing(token_list, token_index, game))
        return true;
    return false;
}

bool accept_inspecting(TokenList token_list, unsigned * token_index, GameState * game)
{
    if (accept_token(token_list, token_index, LOOK))
    {
        accept_token(token_list, token_index, AT);
        if (accept_token(token_list, token_index, ITEM))
        {
            ItemID item_id = token_list.tokens[*token_index-1].value;
            if (is_item_in_room(*game, item_id))
            {
                Item item = game->items[item_id];
                put_text("%s\n", item.description);
                return true;
            }
        }
        put_text("Sorry, that item is not in the room.\n");
        return true;
    }
    return false;
}

bool accept_taking(TokenList token_list, unsigned * token_index, GameState * game)
{
    return false;
}

bool accept_placing(TokenList token_list, unsigned * token_index, GameState * game)
{
    return false;
}

bool accept_movement(TokenList token_list, unsigned * token_index, GameState * game)
{
    if (accept_token(token_list, token_index, WALK) && accept_token(token_list, token_index, DIRECTION))
    {
        Direction direction = token_list.tokens[*token_index-1].value;
        RoomID go_to_room = game->rooms[game->current_room].neighbour_rooms[direction];
        if (go_to_room == ID_NO_ROOM)
        {
            put_text("BONK!\nYou just bumped into a wall...\n");
            return true;
        }
        game->current_room = go_to_room;
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