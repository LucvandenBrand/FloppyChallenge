#ifndef GAME_LOADER_H
#define GAME_LOADER_H

#include <game/game.h>

void load_game_data(GameState * game, const char * game_data_path);
void load_game_from_json_string(GameState * game, const char * game_data_string);
void load_game_from_json_tokens(GameState * game, const char * json_string, jsmntok_t * tokens, int num_tokens);
Room load_room_from_json_tokens(const char * json_string, jsmntok_t * tokens, int num_children, unsigned int * token_index);
Door load_door_from_json_tokens(const char * json_string, jsmntok_t * tokens, int num_children, unsigned int * token_index);
Item load_item_from_json_tokens(const char * json_string, jsmntok_t * tokens, int num_children, unsigned int * token_index);
char * copy_json_string_token(const char * json_string, jsmntok_t token);

#endif
