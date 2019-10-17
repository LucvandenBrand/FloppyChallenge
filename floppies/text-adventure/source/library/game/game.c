#include <game/game.h>
#include <io/text_interface.h>
#include <string.h>
#include <stdlib.h>
#include <game/room.h>
#include <io/files.h>

void game_loop()
{
    GameState game = init_game_state(GAME_DATA_PATH);
    char input[MAX_INPUT_SIZE] = "";
    while (game.is_running)
    {
        put_text("YOU: ");
        get_text(input);
        apply_input_to_game_state(input, &game);
    }
    free_game_state(&game);
}

GameState init_game_state(const char * game_data_path)
{
    GameState game;
    game.is_running = true;
    game.player = init_player();
    game.num_rooms = 0;
    game.max_rooms = 4;
    game.rooms = malloc(game.max_rooms * sizeof(Room));
    game.max_items = 4;
    game.items = malloc(game.max_items * sizeof(Item));
    load_game_data(&game, game_data_path);
    return game;
}

void load_game_data(GameState * game, const char * game_data_path)
{
    long buffer_size = get_file_size(game_data_path);
    if (buffer_size <= 0)
    {
        put_color_text(RED, "Could not find game data file: %s. Exiting game.", game_data_path);
        game->is_running = false;
        return;
    }
    char * game_data_string = malloc(buffer_size * sizeof(char));
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
    jsmntok_t * tokens = malloc(num_tokens * sizeof(jsmntok_t));
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
        if (json_equal(json_string, &tokens[token_index], "rooms") == 0)
        {
            token_index++;
            game->num_rooms = tokens[token_index].size;
            token_index++;
            for (unsigned room_num=0; room_num < game->num_rooms; room_num++)
            {
                if (tokens[token_index].type != JSMN_OBJECT)
                {
                    put_color_text(RED, "The room list should only contain room objects!");
                    game->is_running = false;
                    return;
                }
                token_index += 2;
                int description_size = tokens[token_index].end - tokens[token_index].start;
                char * description = malloc(description_size * sizeof(char));
                strncpy(description, json_string + tokens[token_index].start, description_size);
                game->rooms[room_num] = init_room(description);
                token_index += 2;
                int num_directions = tokens[token_index].size;
                for (Direction direction=0; direction < num_directions; direction++)
                {
                    token_index++;
                    char * room_id_string = strndup(json_string + tokens[token_index].start,
                                                    tokens[token_index].end - tokens[token_index].start);
                    int room_id = atoi(room_id_string);
                    game->rooms[room_num].neighbour_rooms[direction] = room_id;
                }

                token_index += 2;
                int num_room_items = tokens[token_index].size;
                for (unsigned item_num = 0; item_num < num_room_items; item_num++)
                {
                    token_index++;
                    char * item_id_string = strndup(json_string + tokens[token_index].start,
                            tokens[token_index].end - tokens[token_index].start);
                    int item_id = atoi(item_id_string);
                    add_item_to_room(&game->rooms[room_num], item_id);
                }
                token_index++;
            }
        }
        else if (json_equal(json_string, &tokens[token_index], "items") == 0)
        {

        }
    }
}

void free_game_state(GameState * game)
{
    game->is_running = false;
    free_player(&game->player);
    for (unsigned room_index = 0; room_index < game->num_rooms; room_index++)
        free_room(&game->rooms[room_index]);
    free(game->rooms);
    game->rooms = NULL;
    game->num_rooms = 0;
    game->max_rooms = 0;
    free(game->items);
    game->items = NULL;
    game->num_items = 0;
    game->max_items = 0;
}

void apply_input_to_game_state(const char * input, GameState * game)
{
    if (strcmp(input, "exit") == 0)
        game->is_running = false;
}
