/*
Methods for streaming bytes in and out of files.
*/

#ifndef FILE_OUTPUT_STREAM_H
#define FILE_OUTPUT_STREAM_H

#include "CoreIncludes.h"
#include "BitArray.h"

typedef struct file_stream_s FileOutputStream;

struct file_stream_s
{
	FILE* File;
	BitArray* Buffer;
};

FileOutputStream* NewFileOutputStream(FILE* file);

void DestroyFileOutputStream(FileOutputStream* stream);

void PushBits(FileOutputStream* stream, BitArray* bitArray);

void FinishOutput(FileOutputStream* stream);

#endif