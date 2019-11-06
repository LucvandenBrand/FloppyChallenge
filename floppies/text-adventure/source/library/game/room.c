#include <game/room.h>
#include <stdlib.h>
#include <string.h>

Room init_room(char * description)
{
    Room room;
    room.description = description;
    room.item_id_list = init_list();
    for (unsigned index=0; index < NUM_DIRECTIONS; index++)
        room.doors[index] = init_door(NULL, NORTH, ID_NO_ROOM, ID_NO_ITEM, false);
    room.num_doors = 0;
    return room;
}

void free_room(Room * room)
{
    free(room->description);
    room->description = NULL;
    free_list(&room->item_id_list);
    for (unsigned index=0; index < NUM_DIRECTIONS; index++)
        free_door(&room->doors[index]);
    room->num_doors = 0;
}

void add_item_to_room(Room * room, ItemID item_id)
{
    add_id(&room->item_id_list, item_id);
}

void remove_item_from_room(Room * room, ItemID item_id)
{
    remove_id(&room->item_id_list, item_id);
}

void add_door_to_room(Room * room, Door door)
{
    if (!room_has_door(*room, door.direction))
        room->num_doors++;
    free_door(&room->doors[door.direction]);
    room->doors[door.direction] = door;
}

bool room_has_door(Room room, Direction direction)
{
    return room.doors[direction].roomId != ID_NO_ROOM;
}

Door get_room_door(Room room, Direction direction)
{
    return room.doors[direction];
}

bool is_item_in_room(Room room, ItemID item_id)
{
    return has_id(room.item_id_list, item_id);
}