#ifndef ROOM_H
#define ROOM_H

#include <game/item.h>
#include <game/door.h>
#include <game/direction.h>
#include <stdbool.h>
#include <id/id_list.h>
#include "door_list.h"
#include "entity.h"

#define ID_NO_ROOM ID_EMPTY

typedef ID RoomID;

typedef struct {
    char * description;
    IDList item_id_list;
    IDList entity_id_list;
    DoorList doors;
} Room;

Room init_room(char * description);
void free_room(Room * room);
void add_item_to_room(Room * room, ItemID item);
void remove_item_from_room(Room * room, ItemID item_id);
bool is_item_in_room(Room room, ItemID item_id);
void add_door_to_room(Room * room, Door door);
bool room_has_door_in_direction(Room room, Direction direction);
bool room_has_door_with_name(Room room, const char * name);
ID get_room_door_id_with_name(Room room, const char * name);
ID get_room_door_id_with_direction(Room room, Direction direction);
void add_entity_to_room(Room * room, EntityID entity_id);

#endif