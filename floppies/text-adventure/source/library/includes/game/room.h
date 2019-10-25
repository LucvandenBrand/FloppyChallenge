#ifndef ROOM_H
#define ROOM_H

#include "game/item.h"
#include <game/direction.h>
#include <stdbool.h>

#define ID_NO_ROOM -1

typedef int RoomID;

typedef struct {
    char * description;
    ItemID * items;
    unsigned num_items;
    unsigned max_items;
    RoomID neighbour_rooms[NUM_DIRECTIONS];
} Room;

Room init_room(char * description);
void free_room(Room * room);
void add_item_to_room(Room * room, ItemID item);
void remove_item_from_room(Room * room, ItemID item_id);
void connect_rooms(Room * from_room, RoomID to_room, Direction direction);
bool is_item_in_room(Room room, ItemID item_id);

#endif