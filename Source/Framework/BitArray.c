#include "BitArray.h"
#include <string.h>

size_t BytesForBits(size_t bits);

size_t BitsInBytes(size_t bytes);

size_t ByteIndex(size_t forBit);

uint8_t ShiftForBit(size_t forBit);

BitArray* NewBitArray(size_t length){
	BitArray* bitArray = calloc(1, sizeof(BitArray));
	size_t bytesForArray = BytesForBits(length);
	bitArray->Bits = calloc(bytesForArray, sizeof(Bit));
	bitArray->MaxCount = BitsInBytes(bytesForArray);
	return bitArray;
}

void Destroy(BitArray* bitArray){
	free(bitArray->Bits);
	free(bitArray);
}

BitArray* Copy(BitArray* original){
	BitArray* copy = NewBitArray(original->MaxCount);
	copy->Bits = calloc(BytesForBits(original->MaxCount), sizeof(Bit));
	memcpy(copy->Bits, original->Bits, BytesForBits(original->Count));
	copy->Count = original->Count;
	return copy;
}

bool PushBit(BitArray* bitArray, Bit bit){
	if (bitArray->Count >= bitArray->MaxCount){
		return False;
	}
	uint8_t bit_to_add = (bit & BIT_MASK) << ShiftForBit(bitArray->Count);
	//Set the pushed bit.
	bitArray->Bits[ByteIndex(bitArray->Count)] |= bit_to_add;
	bitArray->Count += 1;
	return True;
}

Bit PopBit(BitArray* bitArray){
	if (bitArray->Count < 1){
		return BIT_ERROR;
	}
	uint8_t shift = ShiftForBit(bitArray->Count - 1);
	uint8_t mask = BIT1 << shift;
	Bit poppedBit = bitArray->Bits[ByteIndex(bitArray->Count - 1)] & mask;
	//Remove the popped bit.
	bitArray->Bits[ByteIndex(bitArray->Count - 1)] &= ~mask;
	bitArray->Count -= 1;
	return poppedBit >> shift;
}

/*
==============================================================
					Private Methods
==============================================================
*/

size_t BytesForBits(size_t bits){
	size_t bytes = bits / BITS_IN_BYTE;
	if (bits % BITS_IN_BYTE != 0){
		bytes += 1;
	}
	return bytes;
}

size_t BitsInBytes(size_t bytes){
	return bytes * BITS_IN_BYTE;
}

size_t ByteIndex(size_t forBit){
	return forBit / BITS_IN_BYTE;
}

uint8_t ShiftForBit(size_t forBit){
	return (BITS_IN_BYTE - ((forBit + 1) % BITS_IN_BYTE)) % BITS_IN_BYTE;
}