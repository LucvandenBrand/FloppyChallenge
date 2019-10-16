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
        jsmntok_t token = tokens[token_index];
        if (json_equal(json_string, &token, "rooms"))
        { // TODO : Parse room.
//            int num_elements = tokens[token_index + 1].size;
//            for (unsigned sub_token_index = 0; sub_token_index < num_elements; sub_token_index++)
//            {
//                int num_room_tokens = tokens[token_index + 1].size;
//                jsmntok_t *room_tokens = &tokens[token_index + 2 + sub_token_index];
//                if (game->num_rooms+1 >= game->max_rooms)
//                {
//                    game->max_rooms *= 2;
//                    game->rooms = realloc(game->rooms, game->max_rooms * sizeof(Room));
//                }
//                load_room_from_json_tokens(&game->rooms[game->num_rooms++], json_string, room_tokens, num_room_tokens);
//            }
//            token_index += num_elements + 1;
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
}

void apply_input_to_game_state(const char * input, GameState * game)
{
    if (strcmp(input, "exit") == 0)
        game->is_running = false;
}
