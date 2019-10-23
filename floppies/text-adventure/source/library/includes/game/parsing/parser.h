#ifndef PARSER_H
#define PARSER_H

#include <game/game.h>
#include <game/parsing/token.h>

typedef struct {
    Token * tokens;
    unsigned length;
} TokenList;

void apply_input_to_game_state(const char * input, GameState * game);
TokenList text_to_tokens(const char * input, GameState game);
void apply_tokens_to_game_state(TokenList token_list, GameState * game);
void free_tokens(TokenList * token_list);

#endif