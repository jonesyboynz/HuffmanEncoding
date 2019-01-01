/*
Defines an array of bytes
*/

#ifndef BYTE_ARRAY_H
#define BYTE_ARRAY_H

#include "CoreIncludes.h"

typedef struct byte_array_s ByteArray;

struct byte_array_s
{
	uint8_t* Data;
	size_t Count;
	size_t MaxCount;
};

ByteArray* NewByteArray(size_t length);

void DestroyByteArray(ByteArray* byteArray);

bool PushByte(ByteArray* byteArray, uint8_t byte);

uint8_t PopByte(ByteArray* byteArray);

ByteArray* Union(ByteArray* byteArray1, ByteArray* byteArray2);

#endif