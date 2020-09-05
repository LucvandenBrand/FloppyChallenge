#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdbool.h>
#include "rule.h"
#include "symbol.h"

typedef struct 
{
    SymbolList axiom;
    RuleList rules;
} LSystem;

void free_system(LSystem * system);

#endif