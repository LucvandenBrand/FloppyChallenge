#include <game/room.h>
#include <stdlib.h>
#include <string.h>

Room init_room(char * description)
{
    Room room;
    room.description = description;
    room.item_id_list = init_list();
    for (unsigned index=0; index < NUM_DIRECTIONS; index++)
        room.doors[index] = NULL;
    return room;
}

void free_room(Room * room)
{
    free(room->description);
    room->description = NULL;
    free_list(&room->item_id_list);
    for (unsigned index=0; index < NUM_DIRECTIONS; index++)
        room->doors[index] = NULL;
}

void add_item_to_room(Room * room, ItemID item_id)
{
    add_id(&room->item_id_list, item_id);
}

void remove_item_from_room(Room * room, ItemID item_id)
{
    remove_id(&room->item_id_list, item_id);
}

void add_door_to_room(Room * room, Direction direction, Door door)
{
    room->doors[direction] = door;
}

bool is_item_in_room(Room room, ItemID item_id)
{
    return has_id(room.item_id_list, item_id);
}