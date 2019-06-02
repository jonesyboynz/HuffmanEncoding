#include "FilePosition.h"

uint32_t FileLength(FILE* file){
	uint32_t initial_position = ftell(file);

	rewind(file);
	fseek(file, 0L, SEEK_END);
	uint32_t size = ftell(file);

	rewind(file);
	fseek(file, initial_position, SEEK_SET);
	return size;
}