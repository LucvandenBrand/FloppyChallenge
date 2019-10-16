#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <game/player.h>
#include "room.h"

#define GAME_DATA_PATH "./data/game_data.json"
#define MAX_INPUT_SIZE 100

typedef struct{
    bool is_running;
    Player player;
    Room * rooms;
    unsigned num_rooms;
    unsigned max_rooms;
    RoomID current_room;
} GameState;

void game_loop();
GameState init_game_state(const char * game_data_path);
void load_game_rooms(GameState * game, const char * game_data_path);
void free_game_state(GameState * game);
void apply_input_to_game_state(const char * input, GameState * game);

#endif