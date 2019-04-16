#include "Deserializer.h"

SymbolTable* DeserializeSymbolTable(FileInputStream* stream){
	SymbolTable* table = NewSymbolTable();
	uint32_t table_length, character, bit_array_length;

	ShiftBitsTo(stream, &table_length, SYMBOL_LENGTH_BITS);

	if (table_length < 2){
		DecodingError("Invalid symbol table size.");
		return NULL;
	}

	//printf("Table length: %d\n", table_length);

	//Process characters
	for (uint32_t i = 0; i < table_length - 1; i++){
		ShiftBitsTo(stream, &character, BITS_IN_BYTE);
		ShiftBitsTo(stream, &bit_array_length, SYSTEM_SYMBOL_MAX_BYTES_LENGTH);
		table->Table[character] = NewSymbol((uint8_t) character, ShiftBitsToArray(stream, (size_t) bit_array_length));
	}

	//Process EOF
	ShiftBitsTo(stream, &bit_array_length, SYSTEM_SYMBOL_MAX_BYTES_LENGTH);
	table->Table[EOF_CHARACTER_VALUE] = NewSymbol((uint8_t) EOF_CHARACTER_VALUE, ShiftBitsToArray(stream, (size_t) bit_array_length));

	return table;
}