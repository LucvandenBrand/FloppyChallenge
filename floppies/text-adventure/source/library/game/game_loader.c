#include <game/game_loader.h>
#include <io/text_interface.h>
#include <io/files.h>
#include <stdlib.h>
#include <string.h>
#include <memory/safe_memory.h>

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

void load_game_from_json_tokens(GameState * game, const char * json_string, jsmntok_t * tokens, int num_tokens)
{
    if (num_tokens < 1 || tokens[0].type != JSMN_OBJECT) {
        put_color_text(RED, "Game data should contain only a single top-level object. Exiting game.");
        game->is_running = false;
        return;
    }
    for (unsigned token_index = 0; token_index < num_tokens; token_index++)
    {
        jsmntok_t token = tokens[token_index];
        if (json_equal(json_string, &tokens[token_index], "introduction") == 0)
        {
            token_index++;
            char * introduction_string = strndup(json_string + tokens[token_index].start,
                    tokens[token_index].end - tokens[token_index].start);
            game->intro_text = introduction_string;
        }
        else if (json_equal(json_string, &tokens[token_index], "win") == 0)
        {
            token_index++;
            char * win_string = strndup(json_string + tokens[token_index].start,
                                                 tokens[token_index].end - tokens[token_index].start);
            game->win_text = win_string;
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
                    put_color_text(RED, "The room id should only contain room objects!");
                    game->is_running = false;
                    return;
                }
                token_index += 2;
                game->rooms[room_num] = init_room(copy_json_string_token(json_string, tokens[token_index]));
                token_index += 2;
                int num_directions = tokens[token_index].size;
                for (Direction direction=0; direction < num_directions; direction++)
                {
                    token_index++;
                    char * room_id_string = strndup(json_string + tokens[token_index].start,
                                                    tokens[token_index].end - tokens[token_index].start);
                    int room_id = atoi(room_id_string);
                    free(room_id_string);
                    //game->rooms[room_num].door[direction] = room_id;
                }

                token_index += 2;
                int num_room_items = tokens[token_index].size;
                for (unsigned item_num = 0; item_num < num_room_items; item_num++)
                {
                    token_index++;
                    char * item_id_string = strndup(json_string + tokens[token_index].start,
                                                    tokens[token_index].end - tokens[token_index].start);
                    int item_id = atoi(item_id_string);
                    free(item_id_string);
                    add_item_to_room(&game->rooms[room_num], item_id);
                }
                token_index++;
            }
            token_index--;
        }
        else if (json_equal(json_string, &tokens[token_index], "items") == 0)
        {
            token_index++;
            game->num_items = tokens[token_index].size;
            game->items = safe_malloc(game->num_items * sizeof(Item));
            token_index++;
            for (unsigned item_num=0; item_num < game->num_items; item_num++)
            {
                if (tokens[token_index].type != JSMN_OBJECT)
                {
                    put_color_text(RED, "The item id should only contain item objects!");
                    game->is_running = false;
                    return;
                }
                token_index += 2;
                char * name = copy_json_string_token(json_string, tokens[token_index]);
                token_index += 2;
                char * description = copy_json_string_token(json_string, tokens[token_index]);
                game->items[item_num] = init_item(name, description);
                token_index++;
            }
        }
    }
}

char * copy_json_string_token(const char * json_string, jsmntok_t token)
{
    int string_size = token.end - token.start;
    char * string = safe_malloc((string_size+1) * sizeof(char));
    strncpy(string, json_string + token.start, string_size);
    string[string_size] = '\0';
    return string;
}