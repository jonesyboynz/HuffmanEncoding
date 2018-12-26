#include "CharacterFrequencies.h"
#include <stdlib.h>
#include <stdio.h>

#define FILE_READ_BUFFER_SIZE 1024

uint8_t* CharacterFrequency(FILE* openFile){
	uint8_t buffer[FILE_READ_BUFFER_SIZE]; //Buffer for file reads.
	uint8_t* array = calloc(CHARACTER_SET_LENGTH, sizeof(uint8_t));

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
