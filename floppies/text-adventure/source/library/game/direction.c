#include <game/direction.h>

Direction mirror_direction(Direction direction)
{
    switch(direction)
    {
        case NORTH:
            return SOUTH;
        case EAST:
            return WEST;
        case SOUTH:
            return NORTH;
        case WEST:
            return EAST;
        default:
            return -1;
    }
}