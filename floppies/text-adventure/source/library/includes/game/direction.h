#ifndef DIRECTION_H
#define DIRECTION_H

#define NUM_DIRECTIONS 4

typedef enum {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
} Direction;

Direction mirror_direction(Direction direction);

#endif