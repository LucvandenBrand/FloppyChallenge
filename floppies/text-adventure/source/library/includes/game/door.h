#ifndef DOOR_H
#define DOOR_H

#include <id/id.h>
#include <game/direction.h>

typedef struct
{
    char * name;
    Direction direction;
    ID roomId;
    ID keyId;
} Door;

Door init_door(char * name, Direction direction, ID roomId, ID keyId);
void free_door(Door * door);

#endif