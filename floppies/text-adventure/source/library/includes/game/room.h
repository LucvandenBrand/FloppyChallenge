#ifndef ROOM_H
#define ROOM_H

#include <game/item.h>
#include <game/door.h>
#include <game/direction.h>
#include <stdbool.h>
#include <id/id_list.h>

#define ID_NO_ROOM ID_EMPTY

typedef ID RoomID;

typedef struct {
    char * description;
    IDList item_id_list;
    Door doors [NUM_DIRECTIONS];
    unsigned num_doors;
} Room;

Room init_room(char * description);
void free_room(Room * room);
void add_item_to_room(Room * room, ItemID item);
void remove_item_from_room(Room * room, ItemID item_id);
void add_door_to_room(Room * room, Door door);
bool room_has_door(Room room, Direction direction);
Door get_room_door(Room room, Direction direction);
Direction get_room_door_direction(Room room, const char * name);
bool is_item_in_room(Room room, ItemID item_id);

#endif