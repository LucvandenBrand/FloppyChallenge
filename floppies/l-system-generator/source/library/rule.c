#include "rule.h"
#include "memory/safe_alloc.h"

RuleList alloc_empty_rule_list()
{
    RuleList list;
    list.length = 0;
    list.space = 2;
    list.rules = safe_malloc(sizeof(Rule) * list.space);
}

void free_rule_list(RuleList * list)
{
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
        list->rules = safe_realloc(list->rules, list->space);
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
