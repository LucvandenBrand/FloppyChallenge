#include "system.h"

void free_system(LSystem * system)
{
    free_symbol_list(&system->axiom);
    free_rule_list(&system->rules);
}