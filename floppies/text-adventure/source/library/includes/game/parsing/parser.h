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
bool accept_action(TokenList token_list, unsigned * token_index, GameState * game);
bool accept_inspecting(TokenList token_list, unsigned * token_index, GameState * game);
bool accept_taking(TokenList token_list, unsigned * token_index, GameState * game);
bool accept_placing(TokenList token_list, unsigned * token_index, GameState * game);
bool accept_locking(TokenList token_list, unsigned * token_index, GameState * game);
bool accept_unlocking(TokenList token_list, unsigned * token_index, GameState * game);
bool accept_killing(TokenList token_list, unsigned * token_index, GameState * game);
bool accept_movement(TokenList token_list, unsigned * token_index, GameState * game);
bool accept_token(TokenList token_list, unsigned * token_index, TokenType expected);
void free_tokens(TokenList * token_list);

#endif