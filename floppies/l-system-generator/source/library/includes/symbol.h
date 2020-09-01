#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdlib.h>

typedef char Symbol;

typedef struct 
{
    Symbol * symbols;
    size_t length;
    size_t space;
} SymbolList;

SymbolList alloc_empty_symbol_list();
SymbolList string_to_symbol_list(const char * string, size_t length);
void free_symbol_list(SymbolList * list);
void add_symbol_to_list(Symbol symbol, SymbolList * list);
void add_symbols_to_list(SymbolList from_list, SymbolList * to_list);
void swap_symbol_lists(SymbolList * first_list, SymbolList * second_list);

#endif