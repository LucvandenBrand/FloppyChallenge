#ifndef MOVE_MAP_H
#define MOVE_MAP_H

#include "system/symbol.h"

typedef struct
{
    SymbolList directions[6];
    float rotation_angle;
} MoveMap;

typedef enum
{
    NONE = -1,
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    ROTATE_LEFT = 4,
    ROTATE_RIGHT = 5
} Direction;

MoveMap alloc_empty_move_map();
void free_move_map(MoveMap * map);
void set_symbol_direction(Symbol symbol, Direction direction, MoveMap * map);
Direction get_symbol_direction(Symbol symbol, MoveMap map);

#endif