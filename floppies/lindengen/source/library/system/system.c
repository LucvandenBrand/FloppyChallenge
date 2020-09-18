#include "system/system.h"

LSystem alloc_empty_system()
{
    LSystem system;
    system.axiom = alloc_empty_symbol_list();
    system.rules = alloc_empty_rule_list();
    return system;
}

void free_system(LSystem * system)
{
    free_symbol_list(&system->axiom);
    free_rule_list(&system->rules);
}