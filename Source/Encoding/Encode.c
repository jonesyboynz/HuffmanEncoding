#include "Encode.h"
#include "CharacterFrequencies.h"
#include "Serializer.h"

#define FILE_INPUT_BUFFER_LENGTH 1024 * 32

void EncodeSymbolTable(FileOutputStream* outputStream, SymbolTable* table);

void EncodeSymbolFile(FILE* inputFile, FileOutputStream* outputStream, SymbolTable* table);

void Encode(FILE* inputFile, FileOutputStream* outputStream){
	//Character frequencies
	Frequency* frequencies = CharacterFrequency(inputFile);

	//Get heap
	HuffHeap* heap = GetHeapFromFrequencies(frequencies);

	//Create huffman tree.
	GenerateTreeWithinHeap(heap);

	//Get symbol table 
	SymbolTable* table = GenerateEncodingSymbols(heap->Heap[HEAP_ROOT_INDEX]);

	//Encode the symbol table and write to file.
	EncodeSymbolTable(outputStream, table);

	//Encode file and write to output.
	EncodeSymbolFile(inputFile, outputStream, table);

	//Ensure the output buffer is written.
	FinishOutput(outputStream);

	//Cleanup.
	free(frequencies);
	DestroyHeapAndAllNodes(heap);
	DestroySymbolTable(table);
}

void EncodeSymbolTable(FileOutputStream* outputStream, SymbolTable* table){
	BitArray* tableData = SerializeSymbolTable(table);
	PushBits(outputStream, tableData);
	Destroy(tableData);
}

void EncodeSymbolFile(FILE* inputFile, FileOutputStream* outputStream, SymbolTable* table){
	uint8_t buffer[FILE_INPUT_BUFFER_LENGTH];

	//TODO: move this elsewhere.
	rewind(inputFile);
	fseek(inputFile, 0L, SEEK_END);
	uint32_t size = ftell(inputFile);
	rewind(inputFile);

	size_t read_bytes = fread(buffer, sizeof(uint8_t), FILE_INPUT_BUFFER_LENGTH, inputFile);
	while(read_bytes > 0){
		for (size_t i = 0; i < read_bytes; i++){
			uint8_t byte = buffer[i];
			PushBits(outputStream, table->Table[byte]->BitArray);
		}
		read_bytes = fread(buffer, sizeof(uint8_t), FILE_INPUT_BUFFER_LENGTH, inputFile);
		printf("[%.8f%%] Encoded\n", (((float) ftell(inputFile)) * 100.0) / ((float) size));
	}

	//Add the EOF character.
	PushBits(outputStream, table->Table[EOF_CHARACTER_VALUE]->BitArray);
}