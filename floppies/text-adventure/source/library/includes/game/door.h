#ifndef DOOR_H
#define DOOR_H

#include <game/id.h>

typedef struct
{
    char * name;
    ID roomId;
    ID keyId;
} Door;

Door init_door(char * name, ID roomId, ID keyId);
void free_door(Door * door);

#endif