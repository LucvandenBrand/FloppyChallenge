#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <game/player.h>
#define JSMN_HEADER
#include <io/jsmn.h>
#include <game/room.h>
#include <game/entity.h>

#define GAME_DATA_PATH "./data/game_data.json"
#define MAX_INPUT_SIZE 100

typedef struct{
    bool is_running;
    char * intro_text;
    char * win_text;
    char * reset_text;
    Player player;
    Room * rooms;
    unsigned num_rooms;
    RoomID previous_room;
    RoomID current_room;
    Item * items;
    unsigned num_items;
    Entity * entities;
    unsigned num_entities;
} GameState;

void game_loop();
GameState init_game_state(const char * game_data_path);
void free_game_state(GameState * game);
ItemID get_item_id(const char * search_name, GameState game);
void update_entities(GameState * game);
void reset_kill_count(GameState * game);
void tick_entity_kill_count(GameState * game);
bool check_kill_player(GameState game);

#endif