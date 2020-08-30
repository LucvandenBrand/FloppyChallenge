#include "rule.h"
#include "memory/safe_alloc.h"

SymbolList alloc_empty_symbol_list()
{
    SymbolList list;
    list.length = 0;
    list.space = 2;
    list.symbols = safe_malloc(sizeof(Symbol) * list.space);
}

void free_symbol_list(SymbolList * list)
{
    free(list->symbols);
    list->symbols = NULL;
    list->space = 0;
    list->length = 0;
}

void add_symbol_to_list(Symbol symbol, SymbolList * list)
{
    list->symbols[list->length++] = symbol;
    if (list->length == list->space)
    {
        list->space *= 2;
        list->symbols = safe_realloc(list->symbols, list->space);
    }
}

void add_symbols_to_list(SymbolList from_list, SymbolList * to_list)
{
    for (size_t index = 0; index < from_list.length; index++)
    {
        Symbol symbol = from_list.symbols[index];
        add_symbol_to_list(symbol, to_list);
    }
}
