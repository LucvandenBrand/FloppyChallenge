#ifndef ROOM_H
#define ROOM_H

#include "game/item.h"
#include <game/direction.h>

#define ID_NO_ROOM -1;

typedef int RoomID;

typedef struct {
    const char * description;
    Item * items;
    unsigned num_items;
    unsigned max_items;
    RoomID neighbour_rooms[NUM_DIRECTIONS];
} Room;

Room init_room(const char * description);
void free_room(Room * room);
void add_item_to_room(Room * room, Item item);
void remove_item_from_room(Room * room, const char * item_name);
void connect_rooms(Room * from_room, RoomID to_room, Direction direction);

#endif