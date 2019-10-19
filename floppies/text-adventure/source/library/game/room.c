#include <game/room.h>
#include <stdlib.h>
#include <string.h>

Room init_room(char * description)
{
    Room room;
    room.description = description;
    room.num_items = 0;
    room.max_items = 4;
    room.items = malloc(room.max_items * sizeof(ItemID));
    for (unsigned index=0; index < NUM_DIRECTIONS; index++)
        room.neighbour_rooms[index] = ID_NO_ROOM;
    return room;
}

void free_room(Room * room)
{
    free(room->description);
    room->description = NULL;
    free(room->items);
    room->items = NULL;
    room->num_items = 0;
    room->max_items = 0;
    for (unsigned index=0; index < NUM_DIRECTIONS; index++)
        room->neighbour_rooms[index] = ID_NO_ROOM;
}

void add_item_to_room(Room * room, ItemID item_id)
{
    if (room->num_items+1 >= room->max_items)
    {
        room->max_items *= 2;
        room->items = realloc(room->items, room->max_items * sizeof(ItemID));
    }
    room->items[room->num_items++] = item_id;
}

void remove_item_from_room(Room * room, ItemID item_id)
{
    for (unsigned item_index = 0; item_index < room->num_items; item_index++)
    {
        if (room->items[item_index] == item_id)
        {
            room->num_items--;
            for (unsigned shift_index = item_index; shift_index < room->num_items; shift_index++)
            {
                room->items[shift_index] = room->items[shift_index + 1];
            }
            break;
        }
    }
}

void connect_rooms(Room * from_room, RoomID to_room, Direction direction)
{
    from_room->neighbour_rooms[direction] = to_room;
}