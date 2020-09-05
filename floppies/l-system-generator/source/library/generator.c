#include <stdio.h>
#include "generator.h"

void generate_system(LSystem * system, unsigned int num_iterations)
{
    for (unsigned int iteration = 0; iteration < num_iterations; iteration++)
    {
        if (system->axiom.length > MAX_AXIOM_SIZE)
        {
            printf("ERROR- Maximum axiom size exceeded!");
            break;
        }
        rewrite_symbols(system);
    }
}

void rewrite_symbols(LSystem * system)
{
    SymbolList next_list = alloc_empty_symbol_list();
    for (size_t index = 0; index < system->axiom.length; index++)
    {
        Symbol symbol = system->axiom.symbols[index];
        int rule_index = search_matching_rule_index(system->rules, symbol);
        if (rule_index < 0)
            add_symbol_to_list(symbol, &next_list);
        else
        {
            Rule rule = system->rules.rules[rule_index];
            add_symbols_to_list(rule.consequent, &next_list);
        }
    }
    swap_symbol_lists(&system->axiom, &next_list);
    free_symbol_list(&next_list);
}