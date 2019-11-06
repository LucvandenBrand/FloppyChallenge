#include <game/game_loader.h>
#include <io/text_interface.h>
#include <io/files.h>
#include <stdlib.h>
#include <string.h>
#include <memory/safe_memory.h>
#include <string/string_ops.h>

void load_game_data(GameState * game, const char * game_data_path)
{
    long buffer_size = get_file_size(game_data_path);
    if (buffer_size <= 0)
    {
        put_color_text(RED, "Could not find game data file: %s. Exiting game.", game_data_path);
        game->is_running = false;
        return;
    }
    char * game_data_string = safe_malloc(buffer_size * sizeof(char));
    load_file(game_data_path, game_data_string, buffer_size);
    load_game_from_json_string(game, game_data_string);
    free(game_data_string);
}

void load_game_from_json_string(GameState * game, const char * game_data_string)
{
    jsmn_parser json_parser;
    jsmn_init(&json_parser);
    int num_tokens = jsmn_parse(&json_parser, game_data_string, strlen(game_data_string), NULL, 0);
    if (num_tokens <= 0)
    {
        put_color_text(RED, "Could not read json from game data. Exiting game.");
        game->is_running = false;
        return;
    }
    jsmntok_t * tokens = safe_malloc(num_tokens * sizeof(jsmntok_t));
    jsmn_init(&json_parser);
    jsmn_parse(&json_parser, game_data_string, strlen(game_data_string), tokens, num_tokens);
    load_game_from_json_tokens(game, game_data_string, tokens, num_tokens);
    free(tokens);
}

static int json_equal(const char *json, jsmntok_t *tok, const char *s)
{
    if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
        strncmp(json + tok->start, s, tok->end - tok->start) == 0)
    {
        return 0;
    }
    return -1;
}

static bool json_to_bool(const char *json, jsmntok_t *tok)
{
    if (tok->type == JSMN_PRIMITIVE && strncmp(json + tok->start, "true", tok->end - tok->start) == 0)
    {
        return true;
    }
    return false;
}

void load_game_from_json_tokens(GameState * game, const char * json_string, jsmntok_t * tokens, int num_tokens)
{
    if (num_tokens < 2 || tokens[0].type != JSMN_OBJECT) {
        put_color_text(RED, "Game data should contain only a single top-level object. Exiting game.");
        game->is_running = false;
        return;
    }
    unsigned token_index = 1;
    while (token_index < num_tokens)
    {
        if (json_equal(json_string, &tokens[token_index], "introduction") == 0)
        {
            token_index++;
            char * introduction_string = strndup(json_string + tokens[token_index].start,
                    tokens[token_index].end - tokens[token_index].start);
            char * escaped_introduction_string = replace_string(introduction_string, "\\n", "\n");
            free(introduction_string);
            game->intro_text = escaped_introduction_string;
            token_index++;
        }
        else if (json_equal(json_string, &tokens[token_index], "win") == 0)
        {
            token_index++;
            char * win_string = strndup(json_string + tokens[token_index].start,
                                                 tokens[token_index].end - tokens[token_index].start);
            char * escaped_win_string = replace_string(win_string, "\\n", "\n");
            free(win_string);
            game->win_text = escaped_win_string;
            token_index++;
        }
        else if (json_equal(json_string, &tokens[token_index], "rooms") == 0)
        {
            token_index++;
            game->num_rooms = tokens[token_index].size;
            game->rooms = safe_malloc(game->num_rooms * sizeof(Room));
            token_index++;
            for (unsigned room_num=0; room_num < game->num_rooms; room_num++)
            {
                if (tokens[token_index].type != JSMN_OBJECT)
                {
                    put_color_text(RED, "The rooms list should only contain room objects!");
                    game->is_running = false;
                    return;
                }
                int num_room_children = tokens[token_index].size;
                token_index++;
                Room room = load_room_from_json_tokens(json_string, tokens, num_room_children, &token_index);
                game->rooms[room_num] = room;
            }
        }
        else if (json_equal(json_string, &tokens[token_index], "items") == 0)
        {
            token_index++;
            game->num_items = tokens[token_index].size;
            game->items = safe_malloc(game->num_items * sizeof(Item));
            token_index++;
            for (unsigned item_num=0; item_num < game->num_items; item_num++)
            {
                int num_item_children = tokens[token_index].size;
                token_index++;
                Item item = load_item_from_json_tokens(json_string, tokens, num_item_children, &token_index);
                game->items[item_num] = item;
            }
        }
        else
        {
            put_color_text(RED, "Unknown data.");
            game->is_running = false;
            return;
        }
    }
}

Room load_room_from_json_tokens(const char * json_string, jsmntok_t * tokens, int num_children, unsigned int * token_index)
{
    Room room = init_room(NULL);
    for (unsigned child_index = 0; child_index < num_children; child_index++)
    {
        if (json_equal(json_string, &tokens[*token_index], "description") == 0)
        {
            (*token_index)++;
            char * description = strndup(json_string + tokens[*token_index].start,
                    tokens[*token_index].end - tokens[*token_index].start);
            room.description = description;
            (*token_index)++;
        }
        else if (json_equal(json_string, &tokens[*token_index], "doors") == 0)
        {
            (*token_index)++;
            unsigned num_doors = tokens[*token_index].size;
            (*token_index)++;
            for (unsigned door_num=0; door_num < num_doors; door_num++)
            {
                int num_door_children = tokens[*token_index].size;
                (*token_index)++;
                Door door = load_door_from_json_tokens(json_string, tokens, num_door_children, token_index);
                add_door_to_room(&room, door);
            }
        }
        else if (json_equal(json_string, &tokens[*token_index], "items") == 0)
        {
            (*token_index)++;
            unsigned num_items = tokens[*token_index].size;
            (*token_index)++;
            for (unsigned item_num=0; item_num < num_items; item_num++)
            {
                char * item_string = strndup(json_string + tokens[*token_index].start,
                        tokens[*token_index].end - tokens[*token_index].start);
                ItemID item_id = atoi(item_string);
                free(item_string);
                add_item_to_room(&room, item_id);
                (*token_index)++;
            }
        }
    }
    return room;
}

Door load_door_from_json_tokens(const char * json_string, jsmntok_t * tokens, int num_children, unsigned int * token_index)
{
    char * name = NULL;
    Direction direction = NORTH;
    ID room_id = ID_NO_ROOM;
    ID key_id = ID_NO_ITEM;
    bool is_locked = false;
    for (unsigned child_index = 0; child_index < num_children; child_index++)
    {
        if (json_equal(json_string, &tokens[*token_index], "name") == 0)
        {
            (*token_index)++;
            name = strndup(json_string + tokens[*token_index].start,
                    tokens[*token_index].end - tokens[*token_index].start);
            (*token_index)++;
        }
        else if (json_equal(json_string, &tokens[*token_index], "direction") == 0)
        {
            (*token_index)++;
            if (json_equal(json_string, &tokens[*token_index], "N") == 0)
                direction = NORTH;
            else if (json_equal(json_string, &tokens[*token_index], "E") == 0)
                direction = EAST;
            else if (json_equal(json_string, &tokens[*token_index], "S") == 0)
                direction = SOUTH;
            else
                direction = WEST;
            (*token_index)++;
        }
        else if (json_equal(json_string, &tokens[*token_index], "key") == 0)
        {
            (*token_index)++;
            char * key_string = strndup(json_string + tokens[*token_index].start,
                    tokens[*token_index].end - tokens[*token_index].start);
            key_id = atoi(key_string);
            free(key_string);
            (*token_index)++;
        }
        else if (json_equal(json_string, &tokens[*token_index], "room") == 0)
        {
            (*token_index)++;
            char * room_string = strndup(json_string + tokens[*token_index].start,
                    tokens[*token_index].end - tokens[*token_index].start);
            room_id = atoi(room_string);
            free(room_string);
            (*token_index)++;
        }
        else if (json_equal(json_string, &tokens[*token_index], "locked") == 0)
        {
            (*token_index)++;
            is_locked = json_to_bool(json_string, &tokens[*token_index]);
            (*token_index)++;
        }
    }
    return init_door(name, direction, room_id, key_id, is_locked);
}

Item load_item_from_json_tokens(const char * json_string, jsmntok_t * tokens, int num_children, unsigned int * token_index)
{
    char * name = NULL;
    char * description = NULL;
    for (unsigned child_index = 0; child_index < num_children; child_index++)
    {
        if (json_equal(json_string, &tokens[*token_index], "name") == 0)
        {
            (*token_index)++;
            name = strndup(json_string + tokens[*token_index].start,
                           tokens[*token_index].end - tokens[*token_index].start);
        }
        else if (json_equal(json_string, &tokens[*token_index], "description") == 0)
        {
            (*token_index)++;
            description = strndup(json_string + tokens[*token_index].start,
                    tokens[*token_index].end - tokens[*token_index].start);
        }
        (*token_index)++;
    }
    return init_item(name, description);
}

char * copy_json_string_token(const char * json_string, jsmntok_t token)
{
    int string_size = token.end - token.start;
    char * string = safe_malloc((string_size+1) * sizeof(char));
    strncpy(string, json_string + token.start, string_size);
    string[string_size] = '\0';
    return string;
}