/*
Defines a stream for reading bytes from a file.
*/

#ifndef FILE_INPUT_STREAM_H
#define FILE_INPUT_STREAM_H

#include "CoreIncludes.h"
#include "BitArray.h"

typedef struct file_input_stream_s {
	FILE* File;
	BitArray* Buffer;
	bool EndOfFile;
} FileInputStream;

FileInputStream* NewFileInputStream(FILE* file);

void DestoryFileInputStream(FileInputStream* stream);

size_t ShiftBitsTo(FileInputStream* stream, uint32_t* value, size_t bits);

BitArray* ShiftBitsToArray(FileInputStream* stream, size_t bits);

#endif