#ifndef LOADER_H
#define LOADER_H

#include <stdbool.h>
#include "system/system.h"
#include "io/jsmn.h"
#include "renderer/movemap.h"

bool try_load_system_from_json_string(LSystem * system, MoveMap * move_map, const char * input_buffer);
bool try_load_system_from_json_tokens(LSystem * system,  MoveMap * move_map, const char * input_buffer, jsmntok_t * tokens, int num_tokens);
bool try_load_rule_from_json_tokens(Rule * rule, const char * input_buffer, jsmntok_t * tokens, int num_tokens, unsigned * token_index);
bool json_equal(const char *json, jsmntok_t *tok, const char *s);
bool json_to_bool(const char *json, jsmntok_t *tok);

#endif