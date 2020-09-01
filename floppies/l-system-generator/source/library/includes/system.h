#ifndef SYSTEM_H
#define SYSTEM_H

#include "rule.h"
#include "symbol.h"

typedef struct 
{
    SymbolList axiom;
    RuleList rules;
} LSystem;

#endif