#include <stdlib.h>
#include <game/door.h>

Door init_door(char * name, Direction direction, ID roomId, ID keyId, bool is_locked)
{
    Door door = {name, direction, roomId, keyId, is_locked};
    return door;
}

void free_door(Door * door)
{
    free(door->name);
    door->name = NULL;
    door->roomId = ID_EMPTY;
    door->keyId = ID_EMPTY;
    door->is_locked = false;
}

bool is_exit_door(Door door)
{
    return door.roomId == ROOM_ID_EXIT;
}

bool is_door_locked(Door door)
{
    return door.is_locked;
}

bool try_lock_door(Door * door, ID key_id)
{
    if (door->keyId != key_id)
        return false;
    door->is_locked = true;
    return true;
}

bool try_unlock_door(Door * door, ID key_id)
{
    if (door->keyId != ID_EMPTY && door->keyId != key_id)
        return false;
    door->is_locked = false;
    return true;
}