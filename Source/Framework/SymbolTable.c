#include "SymbolTable.h"

SymbolTable* NewSymbolTable(){
	return calloc(1, sizeof(SymbolTable));
}

void DestroySymbolTable(SymbolTable* table){
	for (uint16_t i = 0; i < SYSTEM_SYMBOL_COUNT; i++){
		if (table->Table[i] != NULL){
			DestroySymbol(table->Table[i]);
		}
	}
	free(table);
}