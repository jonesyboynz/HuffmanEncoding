/*
Defines a table of symbols.
*/

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "CoreIncludes.h"
#include "Symbol.h"

typedef struct symbol_table_s SymbolTable;

struct symbol_table_s{
	Symbol* Table[SYSTEM_SYMBOL_COUNT];
};

SymbolTable* NewSymbolTable();

void DestroySymbolTable(SymbolTable* table);

#endif