#include <game/room.h>
#include <stdlib.h>
#include <string.h>

Room init_room(char * description)
{
    Room room;
    room.description = description;
    room.item_id_list = init_list();
    room.entity_id_list = init_list();
    room.doors = init_door_list();
    return room;
}

void free_room(Room * room)
{
    free(room->description);
    room->description = NULL;
    free_list(&room->item_id_list);
    free_list(&room->entity_id_list);
    free_door_list(&room->doors);
}

void add_item_to_room(Room * room, ItemID item_id)
{
    add_id(&room->item_id_list, item_id);
}

void remove_item_from_room(Room * room, ItemID item_id)
{
    remove_id(&room->item_id_list, item_id);
}

bool is_item_in_room(Room room, ItemID item_id)
{
    return has_id(room.item_id_list, item_id);
}

void add_door_to_room(Room * room, Door door)
{
    add_door(&room->doors, door);
}

bool room_has_door_in_direction(Room room, Direction direction)
{
    return has_door_with_direction(room.doors, direction);
}

bool room_has_door_with_name(Room room, const char * name)
{
    return has_door_with_name(room.doors, name);
}

ID get_room_door_id_with_name(Room room, const char * name)
{
    return get_door_id_with_name(room.doors, name);
}

ID get_room_door_id_with_direction(Room room, Direction direction)
{
    return get_door_id_with_direction(room.doors, direction);
}

void add_entity_to_room(Room * room, EntityID entity_id)
{
    add_id(&room->entity_id_list, entity_id);
}

