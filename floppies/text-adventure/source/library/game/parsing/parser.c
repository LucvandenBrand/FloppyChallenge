#include <game/parsing/parser.h>
#include <stdlib.h>
#include <string.h>

void apply_input_to_game_state(const char * input, GameState * game)
{
    TokenList token_list = text_to_tokens(input);
    apply_tokens_to_game_state(token_list, game);
    free_tokens(&token_list);
}

TokenList text_to_tokens(const char * input)
{
    TokenList tokens = {NULL, 0};
    int max_num_tokens = 0;
    unsigned long num_chars = strlen(input);
    unsigned long start = 0, end = 1;
    while (end < num_chars)
    {
        const char * sub_string = strndup(input + start, end - start);
        Token token = match_token(sub_string);
        if (token.type != NONE)
        {
            // TODO: Append token to tokens. Use max num tokens.
            start = end;
        }
        end++;
    }
    return tokens;
}

Token match_token(const char * string)
{
    Token token = {NONE, 0};
    // TODO: Parse token.
    return token;
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