#include "CharacterFrequencies.h"
#include <stdlib.h>
#include <stdio.h>

#define FILE_READ_BUFFER_SIZE 1024

uint32_t* CharacterFrequency(FILE* openFile){
	uint8_t buffer[FILE_READ_BUFFER_SIZE]; //Buffer for file reads.
	uint32_t* array = calloc(SYSTEM_SYMBOL_COUNT, sizeof(uint32_t));

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

HuffHeap* GetHeapFromFrequencies(uint32_t* frequencies){
	HuffHeap* heap = NewHuffHeap();
	for(uint16_t i = 0; i < SYSTEM_SYMBOL_COUNT; i++){
		if (frequencies[i] > 0){
			HuffNode* node = NewHuffNode((uint8_t) i, frequencies[i]);
			Add(heap, node);
		}
	}
	return heap;
}