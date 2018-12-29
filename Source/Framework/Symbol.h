/*
Huffman encoded symbol
*/

#ifndef SYMBOL_H
#define SYMBOL_H

#include "CoreIncludes.h"
#include "BitArray.h"

typedef struct symbol_s Symbol;

struct symbol_s
{
	uint8_t Character;
	BitArray* BitArray;
};

Symbol* NewSymbol(uint8_t character, BitArray* bitArray);

void DestroySymbol(Symbol* symbol);

#endif