#ifndef DOOR_H
#define DOOR_H

#include <id/id.h>
#include <game/direction.h>
#include <stdbool.h>

#define ROOM_ID_EXIT -2

typedef struct
{
    char * name;
    Direction direction;
    ID roomId;
    ID keyId;
} Door;

Door init_door(char * name, Direction direction, ID roomId, ID keyId);
void free_door(Door * door);
bool is_exit_door(Door door);

#endif