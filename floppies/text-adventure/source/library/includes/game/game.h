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
void free_game_state(GameState * game);

#endif