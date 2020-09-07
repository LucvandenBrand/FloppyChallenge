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
        printf("System data should contain only a single top-level object.\n");
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
            SymbolList axiom = string_to_symbol_list(axiom_string, axiom_length);
            add_symbols_to_list(axiom, &system->axiom);
            free(axiom_string);
            free_symbol_list(&axiom);
            token_index++;
        }
        else if (json_equal(input_buffer, &tokens[token_index], "rules"))
        {
            token_index++;
            int num_rules = tokens[token_index].size;
            token_index++;
            for (size_t rule_index = 0; rule_index < num_rules; rule_index++)
            {
                if (tokens[token_index].type != JSMN_OBJECT)
                {
                    printf("The rule list should only contain rule objects.\n");
                    return false;
                }
                int num_rule_children = tokens[token_index].size;
                token_index++;
                Rule rule;
                if (try_load_rule_from_json_tokens(&rule, input_buffer, tokens, num_rule_children, &token_index))
                    add_rule_to_list(rule, &system->rules);
            }
        }
        else
        {
            printf("Unknown system attribute.\n");
            return false;
        }
    }
    return true;
}

bool try_load_rule_from_json_tokens(Rule * rule, const char * input_buffer, jsmntok_t * tokens, int num_children, unsigned * token_index)
{
    for (unsigned child_index = 0; child_index < num_children; child_index++) {
        if (json_equal(input_buffer, &tokens[*token_index], "antecedent")) {
            (*token_index)++;
            int antecedent_length = tokens[*token_index].end - tokens[*token_index].start;
            if (antecedent_length < 1)
            {
                printf("The antecedent of a rule is empty.\n");
                return false;
            }

            char *antecedent = strndup(input_buffer + tokens[*token_index].start, antecedent_length);
            rule->antecedent = antecedent[0];
            free(antecedent);
            (*token_index)++;
        }
        else if (json_equal(input_buffer, &tokens[*token_index], "consequent")) {
            (*token_index)++;
            int consequent_length = tokens[*token_index].end - tokens[*token_index].start;
            if (consequent_length < 1)
            {
                printf("The consequent of a rule is empty.\n");
                return false;
            }

            char *consequent = strndup(input_buffer + tokens[*token_index].start, consequent_length);
            rule->consequent = string_to_symbol_list(consequent, consequent_length);
            free(consequent);
            (*token_index)++;
        }
        else {
            printf("Unknown rule attribute.\n");
            return false;
        }
    }
    return true;
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