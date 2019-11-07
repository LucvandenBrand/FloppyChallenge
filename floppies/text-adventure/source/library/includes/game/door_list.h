#ifndef DOOR_LIST_H
#define DOOR_LIST_H

#include <game/door.h>

typedef struct {
    Door * doors;
    int num_doors;
    int list_size;
} DoorList;

DoorList init_door_list();
void free_door_list(DoorList * list);
void add_door(DoorList * list, Door door);
bool has_door_with_name(DoorList list, const char * name);
bool has_door_with_direction(DoorList list, Direction direction);
ID get_door_id_with_name(DoorList list, const char * name);
ID get_door_id_with_direction(DoorList list, Direction direction);

#endif