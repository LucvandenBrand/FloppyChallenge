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
    bool is_locked;
} Door;

Door init_door(char * name, Direction direction, ID roomId, ID keyId, bool is_locked);
void free_door(Door * door);
bool is_exit_door(Door door);
bool is_door_locked(Door door);
bool try_lock_door(Door * door, ID key_id);
bool try_unlock_door(Door * door, ID key_id);

#endif