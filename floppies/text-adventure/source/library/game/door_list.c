#include <game/door_list.h>
#include <stdlib.h>
#include <memory/safe_memory.h>
#include <string.h>
#include <string/string_ops.h>

DoorList init_door_list()
{
    DoorList list;
    list.list_size = 4;
    list.num_doors = 0;
    list.doors = malloc(list.list_size * sizeof(Door));
    return list;
}

void free_door_list(DoorList * list)
{
    for (ID id = 0; id < list->num_doors; id++)
        free_door(&list->doors[id]);
    free(list->doors);
    list->doors = NULL;
    list->list_size = 0;
    list->num_doors = 0;
}

void add_door(DoorList * list, Door door)
{
    if (has_door_with_direction(*list, door.direction))
    {
        ID id = get_door_id_with_direction(*list, door.direction);
        free_door(&list->doors[id]);
        list->doors[id] = door;
        return;
    }

    if (list->num_doors+1 >= list->list_size)
    {
        list->list_size *= 2;
        list->doors = safe_realloc(list->doors, list->list_size * sizeof(Door));
    }
    list->doors[list->num_doors++] = door;
}

bool has_door_with_name(DoorList list, const char * name)
{
    return get_door_id_with_name(list, name) != ID_EMPTY;
}

bool has_door_with_direction(DoorList list, Direction direction)
{
    return get_door_id_with_direction(list, direction) != ID_EMPTY;
}

ID get_door_id_with_name(DoorList list, const char * name)
{
    for (ID id=0; id < list.num_doors; id++)
    {
        const char * door_name = list.doors[id].name;
        unsigned long door_name_length = strlen(door_name);
        unsigned long name_length = strlen(name);
        if (door_name_length != name_length)
            continue;

        char * lower_door_name = safe_malloc((door_name_length + 1) * sizeof(char));
        strncpy(lower_door_name, door_name, door_name_length + 1);
        string_to_lowercase(lower_door_name, door_name_length);
        int equality = strncmp(lower_door_name, name, door_name_length);
        free(lower_door_name);

        if (equality == 0)
            return id;
    }
    return ID_EMPTY;
}

ID get_door_id_with_direction(DoorList list, Direction direction)
{
    for (ID id=0; id < list.num_doors; id++)
        if (list.doors[id].name != NULL && list.doors[id].direction == direction)
            return id;
    return ID_EMPTY;
}