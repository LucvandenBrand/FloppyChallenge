#ifndef TOKEN_H
#define TOKEN_H

#include <game/game.h>

/**
 * Grammar: STATEMENT := ACTION | MOVEMENT | EXIT
 *          ACTION := INSPECTING | TAKING | PLACING
 *          INSPECTING := LOOK {AT} ITEM | ROOM | INVENTORY
 *          TAKING := TAKE ITEM
 *          PLACING := PLACE ITEM
 *          ITEM := [a-Z]+
 *          MOVEMENT := WALK DIRECTION
 *          DIRECTION := north | east | south | west
 */
typedef enum {
    NONE = -1,
    LOOK = 0,
    AT,
    TAKE,
    PLACE,
    ITEM,
    ROOM,
    INVENTORY,
    WALK,
    DIRECTION,
    EXIT
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

Token match_token(const char * string, GameState game);

#endif