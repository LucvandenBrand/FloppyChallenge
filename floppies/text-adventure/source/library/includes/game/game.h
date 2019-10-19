#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <game/player.h>
#define JSMN_HEADER
#include <io/jsmn.h>
#include "room.h"

#define GAME_DATA_PATH "./data/game_data.json"
#define MAX_INPUT_SIZE 100

typedef struct{
    bool is_running;
    Player player;
    Room * rooms;
    unsigned num_rooms;
    RoomID current_room;
    Item * items;
    unsigned num_items;
} GameState;

void game_loop();
GameState init_game_state(const char * game_data_path);
void load_game_data(GameState * game, const char * game_data_path);
void load_game_from_json_string(GameState * game, const char * game_data_string);
void load_game_from_json_tokens(GameState * game, const char * json_string, jsmntok_t * tokens, int num_tokens);
void free_game_state(GameState * game);
void describe_room(GameState game, RoomID room_id);
void apply_input_to_game_state(const char * input, GameState * game);

#endif