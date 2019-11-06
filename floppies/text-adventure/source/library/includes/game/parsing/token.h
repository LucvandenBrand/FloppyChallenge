#ifndef TOKEN_H
#define TOKEN_H

#include <game/game.h>

/**
 * Grammar: STATEMENT := ACTION | MOVEMENT | EXIT
 *          ACTION := INSPECTING | TAKING | PLACING | LOCKING | UNLOCKING
 *          INSPECTING := LOOK {AT} ITEM | ROOM | INVENTORY
 *          TAKING := TAKE ITEM
 *          PLACING := PLACE ITEM
 *          LOCKING := LOCK DOOR WITH ITEM
 *          UNLOCKING := UNLOCK | OPEN DOOR WITH ITEM
 *          DOOR := [a-Z]+
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
    EXIT,
    LOCK,
    UNLOCK,
    OPEN,
    WITH
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

Token match_token(const char * string, GameState game);

#endif