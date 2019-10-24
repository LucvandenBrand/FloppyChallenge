#ifndef TOKEN_H
#define TOKEN_H

#include <game/game.h>

/**
 * Grammar: STATEMENT := ACTION | MOVEMENT | EXIT
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
    DIRECTION,
    EXIT
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

Token match_token(const char * string, GameState game);

#endif