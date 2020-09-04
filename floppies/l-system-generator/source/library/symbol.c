#include "rule.h"
#include "memory/safe_alloc.h"

SymbolList alloc_empty_symbol_list()
{
    SymbolList list;
    list.length = 0;
    list.space = 2;
    list.symbols = safe_malloc(sizeof(Symbol) * list.space);
    return list;
}

SymbolList string_to_symbol_list(const char * string, size_t length)
{
    SymbolList list = alloc_empty_symbol_list();
    for (size_t index = 0; index < length; index++)
    {
        Symbol symbol = string[index];
        add_symbol_to_list(symbol, &list);
    }
    return list;
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
        list->symbols = safe_realloc(list->symbols, sizeof(Symbol) * list->space);
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

void swap_symbol_lists(SymbolList * first_list, SymbolList * second_list)
{
    SymbolList temp_list = {first_list->symbols, first_list->length, first_list->space};
    first_list->symbols = second_list->symbols;
    first_list->length = second_list->length;
    first_list->space = second_list->space;

    second_list->symbols = temp_list.symbols;
    second_list->length = temp_list.length;
    second_list->space = temp_list.space;
}