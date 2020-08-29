#ifndef RULE_H
#define RULE_H

#include "stdlib.h"
#include "./symbol.h"

typedef struct 
{
    const Symbol antecedent;
    const Symbol * consequent;
    size_t rewrite_length;
} Rule;

typedef struct 
{
    Rule * rules;
    size_t length;
    size_t space;
} RuleList;

RuleList alloc_empty_rule_list();
void free_rule_list(RuleList * list);
void add_rule_to_list(Rule rule, RuleList * list);
int search_matching_rule_index(RuleList list, Symbol query);

#endif