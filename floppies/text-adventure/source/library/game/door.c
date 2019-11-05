#include <stdlib.h>
#include <game/door.h>

Door init_door(char * name, Direction direction, ID roomId, ID keyId)
{
    Door door = {name, direction, roomId, keyId};
    return door;
}

void free_door(Door * door)
{
    free(door->name);
    door->name = NULL;
    door->roomId = ID_EMPTY;
    door->keyId = ID_EMPTY;
}

bool is_exit_door(Door door)
{
    return door.roomId == ROOM_ID_EXIT;
}