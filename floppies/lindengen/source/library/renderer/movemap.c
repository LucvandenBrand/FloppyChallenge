#include "renderer/movemap.h"
#include "memory/safe_alloc.h"

MoveMap alloc_empty_move_map()
{
    MoveMap map;
    for (size_t index = 0; index < 6; index++)
        map.directions[index] = alloc_empty_symbol_list();
    map.rotation_angle = 0;
    return map;
}

void free_move_map(MoveMap * map)
{
    for (size_t index = 0; index < 6; index++)
        free_symbol_list(&map->directions[index]);
    map->rotation_angle = 0;
}

void set_symbol_direction(Symbol symbol, Direction direction, MoveMap * map)
{
    if (direction == NONE || symbol_in_list(symbol, map->directions[direction]))
        return;
    add_symbol_to_list(symbol, &map->directions[direction]);
}

Direction get_symbol_direction(Symbol symbol, MoveMap map)
{
    for (size_t index = 0; index < 6; index++)
    {
        if (symbol_in_list(symbol, map.directions[index]))
            return index;
    }
    return NONE;
}