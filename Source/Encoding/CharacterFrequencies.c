#include "CharacterFrequencies.h"

#define FILE_READ_BUFFER_SIZE 1024

Frequency* CharacterFrequency(FILE* openFile){
	uint8_t buffer[FILE_READ_BUFFER_SIZE]; //Buffer for file reads.
	Frequency* array = calloc(SYSTEM_SYMBOL_COUNT, sizeof(Frequency));

	//loop over the file.
	size_t bytes_read = fread(buffer, sizeof(uint8_t), FILE_READ_BUFFER_SIZE, openFile);
	while(bytes_read > 0){
		for (uint16_t i = 0; i < bytes_read; i++){
			array[buffer[i]] += 1;
		}
		bytes_read = fread(buffer, sizeof(uint8_t), FILE_READ_BUFFER_SIZE, openFile);
	}

	return array;
}

HuffHeap* GetHeapFromFrequencies(Frequency* frequencies){
	HuffHeap* heap = NewHuffHeap();
	Add(heap, NewHuffNode(BYTE_UNUSED, SYMBOL_TYOE_EOF, 1)); //Adds the EOF character to the heap first.
	for(uint16_t i = 0; i < SYSTEM_SYMBOL_COUNT; i++){
		if (frequencies[i] > 0){
			HuffNode* node = NewHuffNode((uint8_t) i, SYMBOL_TYPE_CHARACTER, frequencies[i]);
			Add(heap, node);
		}
	}
	return heap;
}