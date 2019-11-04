#include <stdlib.h>
#include <game/door.h>

Door init_door(char * name, ID roomId, ID keyId)
{
    Door door = {name, roomId, keyId};
    return door;
}

void free_door(Door * door)
{
    free(door->name);
    door->name = NULL;
    door->roomId = ID_EMPTY;
    door->keyId = ID_EMPTY;
}