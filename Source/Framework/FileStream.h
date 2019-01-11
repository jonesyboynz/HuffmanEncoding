/*
Methods for streaming bytes in and out of files.
*/

#ifndef FILE_STREAM_H
#define FILE_STREAM_H

#include "CoreIncludes.h"
#include "BitArray.h"

typedef struct file_stream_s FileStream;

struct file_stream_s
{
	FILE* File;
	BitArray* Buffer;
};

FileStream* NewFileStream(FILE* file);

void DestroyFileStream(FileStream* stream);

void PushBits(FileStream* stream, BitArray* bitArray);

void FinishOutput(FileStream* stream);

#endif