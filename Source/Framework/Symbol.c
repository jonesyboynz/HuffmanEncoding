#include "Symbol.h"
#include <stdlib.h>

Symbol* NewSymbol(uint8_t character, BitArray* bitArray){
	Symbol* newSymbol = calloc(1, sizeof(Symbol));
	newSymbol->Character = character;
	newSymbol->BitArray = bitArray;
	return newSymbol;
}

void DestroySymbol(Symbol* symbol){
	Destroy(symbol->BitArray);
	free(symbol);
}