#ifndef RULE_H
#define RULE_H

#include <stdlib.h>
#include "./symbol.h"

typedef struct 
{
    Symbol antecedent;
    SymbolList consequent;
} Rule;

typedef struct 
{
    Rule * rules;
    size_t length;
    size_t space;
} RuleList;

Rule alloc_rule(char antecedent, const char * consequent);
void free_rule(Rule * rule);
RuleList alloc_empty_rule_list();
void free_rule_list(RuleList * list);
void add_rule_to_list(Rule rule, RuleList * list);
int search_matching_rule_index(RuleList list, Symbol query);

#endif