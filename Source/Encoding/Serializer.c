#include "Serializer.h"

//TODO : move these constants elsewhere.
#define TABLE_LENGTH_BITS 9

size_t SymbolTableRequiredBits(SymbolTable* table);

BitArray* SerializeSymbolTable(SymbolTable* table){
	
	BitArray* array = NewBitArray(SymbolTableRequiredBits(table));

	uint16_t length = TableCount(table);
	PushByteSlice(array, (uint8_t) (length >> BITS_IN_BYTE), 0, 1); //Shift on the first bit of the length
	PushByteSlice(array, (uint8_t) length, 0, BITS_IN_BYTE);		//Shift on the first 8 bytes of the length

	for (uint16_t i = 0; i < SYSTEM_SYMBOL_COUNT; i++){

		if (table->Table[i] != NULL && i != EOF_CHARACTER_VALUE){

			//Push the character to the bit array.
			PushByteSlice(array, table->Table[i]->Character, 0, BITS_IN_BYTE);

			//Push the symbol size to the bit array.
			PushByteSlice(array,
				(uint8_t) table->Table[i]->BitArray->Count, 0, SYMBOL_LENGTH_BITS);

			//Append the symbol to the bit array.
			Append(array, table->Table[i]->BitArray);
		}

		//Push the EOF character to the bit array as the final character.
		PushByteSlice(array,
				(uint8_t) table->Table[EOF_CHARACTER_VALUE]->BitArray->Count, 0, SYMBOL_LENGTH_BITS);
		Append(array, table->Table[EOF_CHARACTER_VALUE]->BitArray);
	}
	return array;
}

//===============================================================================
//								PRIVATE METHODS
//===============================================================================

size_t SymbolTableRequiredBits(SymbolTable* table){
	size_t length = TABLE_LENGTH_BITS;

	for (uint16_t i = 0; i < SYSTEM_SYMBOL_COUNT; i++){
		if (i == EOF_CHARACTER_VALUE){
			length += SYMBOL_LENGTH_BITS
				+ table->Table[EOF_CHARACTER_VALUE]->BitArray->Count;
		}
		else if (table->Table[i] != NULL){
			length += BITS_IN_BYTE //Character
				+ SYMBOL_LENGTH_BITS //Number of bits in the symbol
				+ table->Table[i]->BitArray->Count; //Symbol.
		}
	}
	return length;
}