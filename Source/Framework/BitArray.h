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

bool PushBit(BitArray* bitArray, Bit bit);

Bit PopBit(BitArray* bitArray);

#endif
