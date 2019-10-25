#ifndef TEXT_GENERATOR_H
#define TEXT_GENERATOR_H

#include <game/game.h>

void describe_room(GameState game, RoomID room_id);
void list_items(GameState game, const ItemID * items, unsigned num_items);
void choose_indefinite_article(const char * name);
bool is_char_in_array(char character, const char * array);

#endif