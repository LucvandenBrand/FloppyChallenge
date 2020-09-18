#ifndef MOVE_MAP_H
#define MOVE_MAP_H

#include "system/symbol.h"

typedef struct
{
    SymbolList directions[3];
    float rotation_angle;
} MoveMap;

typedef enum
{
    NONE = -1,
    MOVE = 0,
    ROTATE_LEFT = 1,
    ROTATE_RIGHT = 2
} Direction;

MoveMap alloc_empty_move_map();
void free_move_map(MoveMap * map);
void set_symbol_direction(Symbol symbol, Direction direction, MoveMap * map);
Direction get_symbol_direction(Symbol symbol, MoveMap map);

#endif