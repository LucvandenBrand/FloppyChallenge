#ifndef TOKEN_H
#define TOKEN_H

/**
 * Grammar: STATEMENT := ACTION | MOVEMENT
 *          ACTION := INSPECTING | TAKING | PLACING | WALKING
 *          INSPECTING := LOOK {AT} ITEM
 *          TAKING := TAKE ITEM
 *          PLACING := PLACE ITEM
 *          ITEM := [a-Z]+
 *          WALKING := WALK DIRECTION
 *          DIRECTION := north | east | south | west
 */
typedef enum {
    NONE = -1,
    LOOK = 0,
    AT,
    TAKE,
    PLACE,
    ITEM,
    WALK,
    DIR_NORTH,
    DIR_EAST,
    DIR_SOUTH,
    DIR_WEST
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

#endif