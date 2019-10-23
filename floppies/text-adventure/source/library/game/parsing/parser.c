#include <game/parsing/parser.h>
#include <stdlib.h>

void apply_input_to_game_state(const char * input, GameState * game)
{
    TokenList token_list = text_to_tokens(input);
    apply_tokens_to_game_state(token_list, game);
    free_tokens(&token_list);
}

TokenList text_to_tokens(const char * input)
{
    TokenList tokens = {NULL, 0};
    return tokens;
}

void apply_tokens_to_game_state(TokenList token_list, GameState * game)
{
    for (unsigned token_index=0; token_index < token_list.length; token_index++)
    {
        Token token = token_list.tokens[token_index];
    }
    game->is_running = false;
}

void free_tokens(TokenList * token_list)
{
    free(token_list->tokens);
    token_list->tokens = NULL;
    token_list->length = 0;
}