#ifndef SYSTEM_H
#define SYSTEM_H

#include "rule.h"
#include "symbol.h"

typedef struct 
{
    const SymbolList axiom;
    const RuleList rules;
} LSystem;

#endif