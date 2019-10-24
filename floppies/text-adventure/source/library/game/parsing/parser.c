#include <game/parsing/parser.h>
#include <stdlib.h>
#include <string.h>

void apply_input_to_game_state(const char * input, GameState * game)
{
    TokenList token_list = text_to_tokens(input, *game);
    apply_tokens_to_game_state(token_list, game);
    free_tokens(&token_list);
}

TokenList text_to_tokens(const char * input, GameState game)
{
    TokenList tokens = {NULL, 0};
    int max_num_tokens = 2;
    tokens.tokens = malloc(max_num_tokens * sizeof(Token));
    unsigned long num_chars = strlen(input);
    unsigned long start = 0, end = 1;
    while (end <= num_chars)
    {
        if (*(input + start) == ' ')
        {
            start = end;
            end++;
            continue;
        }

        const char * sub_string = strndup(input + start, end - start);
        Token token = match_token(sub_string, game);
        if (token.type != NONE)
        {
            if (tokens.length >= max_num_tokens)
            {
                max_num_tokens *= 2;
                tokens.tokens = realloc(tokens.tokens, max_num_tokens * sizeof(Token));
            }
            tokens.tokens[tokens.length++] = token;
            start = end;
        }
        end++;
    }
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