#include <string.h>
#include <stdio.h>
#include "memory/safe_alloc.h"
#include "loader.h"

bool try_load_system_from_json_string(LSystem * system, const char * input_buffer)
{
    jsmn_parser json_parser;
    jsmn_init(&json_parser);
    int num_tokens = jsmn_parse(&json_parser, input_buffer, strlen(input_buffer), NULL, 0);
    if (num_tokens <= 0)
        return false;
    jsmntok_t * tokens = safe_malloc(num_tokens * sizeof(jsmntok_t));
    jsmn_init(&json_parser);
    jsmn_parse(&json_parser, input_buffer, strlen(input_buffer), tokens, num_tokens);
    bool success_status = try_load_system_from_json_tokens(system, input_buffer, tokens, num_tokens);
    free(tokens);
    return success_status;
}

bool try_load_system_from_json_tokens(LSystem * system, const char * input_buffer, jsmntok_t * tokens, int num_tokens)
{
    if (num_tokens < 2 || tokens[0].type != JSMN_OBJECT) {
        printf("System data should contain only a single top-level object.");
        return false;
    }

    unsigned token_index = 1;
    while (token_index < num_tokens)
    {
        if (json_equal(input_buffer, &tokens[token_index], "axiom"))
        {
            token_index++;
            size_t axiom_length = tokens[token_index].end - tokens[token_index].start;
            char * axiom_string = strndup(input_buffer + tokens[token_index].start, axiom_length);
            system->axiom = string_to_symbol_list(axiom_string, axiom_length);
            free(axiom_string);
            token_index++;
        }
        else
        {
            printf("Unknown attribute.\n");
            return false;
        }
    }
}

bool json_equal(const char *json, jsmntok_t *tok, const char *s)
{
    if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
        strncmp(json + tok->start, s, tok->end - tok->start) == 0)
    {
        return true;
    }
    return false;
}

bool json_to_bool(const char *json, jsmntok_t *tok)
{
    if (tok->type == JSMN_PRIMITIVE && strncmp(json + tok->start, "true", tok->end - tok->start) == 0)
    {
        return true;
    }
    return false;
}