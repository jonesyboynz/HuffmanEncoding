#include "Encode.h"
#include "Serializer.h"

#define FILE_INPUT_BUFFER_LENGTH 1024

void EncodeSymbolTable(FileOutputStream* outputStream, SymbolTable* table);

void EncodeSymbolFile(FILE* inputFile, FileOutputStream* outputStream, SymbolTable* table);

void Encode(FILE* inputFile, FileOutputStream* outputStream, SymbolTable* table){		
	EncodeSymbolTable(outputStream, table);
	EncodeSymbolFile(inputFile, outputStream, table);
	FinishOutput(outputStream);
}

void EncodeSymbolTable(FileOutputStream* outputStream, SymbolTable* table){
	BitArray* tableData = SerializeSymbolTable(table);

	printf("WRITING SYMBOL TABLE:\n");
	DISPLAY_BIT_ARRAY_DEF(tableData);

	PushBits(outputStream, tableData);
	Destroy(tableData);
}

void EncodeSymbolFile(FILE* inputFile, FileOutputStream* outputStream, SymbolTable* table){
	uint8_t buffer[FILE_INPUT_BUFFER_LENGTH];

	printf("ENCODING SYMBOLS:\n");

	size_t read_bytes = fread(buffer, sizeof(uint8_t), FILE_INPUT_BUFFER_LENGTH, inputFile);

	while(read_bytes > 0){
		for (size_t i = 0; i < read_bytes; i++){
			uint8_t byte = buffer[i];
			printf("%c: ", byte);
			DISPLAY_BIT_ARRAY_DEF(table->Table[byte]->BitArray);
			PushBits(outputStream, table->Table[byte]->BitArray);
		}
		read_bytes = fread(buffer, sizeof(uint8_t), FILE_INPUT_BUFFER_LENGTH, inputFile);
	}

	DISPLAY_BIT_ARRAY_DEF(table->Table[EOF_CHARACTER_VALUE]->BitArray);

	//Add the EOF character
	PushBits(outputStream, table->Table[EOF_CHARACTER_VALUE]->BitArray);

	printf("DONE\n");
}