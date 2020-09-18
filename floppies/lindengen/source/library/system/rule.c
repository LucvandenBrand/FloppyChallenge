#include <memory.h>
#include "system/rule.h"
#include "memory/safe_alloc.h"

Rule alloc_empty_rule()
{
    Rule rule;
    rule.antecedent = '\0';
    rule.consequent = alloc_empty_symbol_list();
    return rule;
}

Rule alloc_rule(char antecedent, const char * consequent)
{
    Rule rule;
    rule.antecedent = antecedent;
    rule.consequent = string_to_symbol_list(consequent, strlen(consequent));
    return rule;
}

void free_rule(Rule * rule)
{
    rule->antecedent = '\0';
    free_symbol_list(&(rule->consequent));
}

RuleList alloc_empty_rule_list()
{
    RuleList list;
    list.length = 0;
    list.space = 2;
    list.rules = safe_malloc(sizeof(Rule) * list.space);
    return list;
}

void free_rule_list(RuleList * list)
{
    for (size_t index = 0; index < list->length; index++)
    {
        free_rule(&list->rules[index]);
    }
    free(list->rules);
    list->rules = NULL;
    list->space = 0;
    list->length = 0;
}

void add_rule_to_list(Rule rule, RuleList * list)
{
    list->rules[list->length++] = rule;
    if (list->length == list->space)
    {
        list->space *= 2;
        list->rules = safe_realloc(list->rules, sizeof(Rule) * list->space);
    }
}

int search_matching_rule_index(RuleList list, Symbol query)
{
    for (size_t index = 0; index < list.length; index++)
    {
        Rule rule = list.rules[index];
        if (rule.antecedent == query)
            return index;
    }
    return -1;
}
