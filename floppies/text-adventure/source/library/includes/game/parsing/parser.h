#ifndef PARSER_H
#define PARSER_H

#include <game/game.h>

typedef enum {
    ITEM
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

typedef struct {
    Token * tokens;
    unsigned length;
} TokenList;

void apply_input_to_game_state(const char * input, GameState * game);
TokenList text_to_tokens(const char * input);
void apply_tokens_to_game_state(TokenList token_list, GameState * game);
void free_tokens(TokenList * token_list);

#endif