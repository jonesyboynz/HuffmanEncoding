/*
Defines an array of bits.
*/

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include "CoreIncludes.h"

typedef struct bit_array_s BitArray;

struct bit_array_s {
	Bit* Bits;
	size_t MaxCount; 	//Max length in BITS
	size_t Count; 		//Current length in BITS	
};

BitArray* NewBitArray(size_t length);

void Destroy(BitArray* bitArray);

BitArray* Copy(BitArray* original);

Bit GetBit(BitArray* bitArray, size_t index);

void SetBit(BitArray* bitArray, size_t index, Bit bit);

bool PushBit(BitArray* bitArray, Bit bit);

bool QuickPushByte(BitArray* bitArray, uint8_t byte);

size_t PushByteSlice(BitArray* bitArray, uint8_t byte, uint8_t fromIndex, uint8_t upToIndex);

Bit PopBit(BitArray* bitArray);

void Clear(BitArray* bitArray);

//Returns the number of bits that have been appended.
size_t Append(BitArray* original, BitArray* appendBits);

size_t BytesForBits(size_t bits);

#endif
