#include "BitArray.h"
#include <string.h>

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

Bit GetBit(BitArray* bitArray, size_t index){
	if (index < 0 || index >= bitArray->Count){
		return BIT_ERROR;
	}
	uint8_t shift = ShiftForBit(index % 8);
	uint8_t mask = BIT1 << shift;
	Bit bit = (bitArray->Bits[ByteIndex(index)] & mask) >> shift;
	return bit;
}

void SetBit(BitArray* bitArray, size_t index, Bit bit){
	if (index < 0 || index > bitArray->MaxCount){
		return;
	}
	uint8_t bit_to_add = (bit & BIT_MASK) << ShiftForBit(index);
	bitArray->Bits[ByteIndex(index)] |= bit_to_add;
	//Update count
	if (bitArray->Count < index + 1){
		bitArray->Count = index + 1;
	}
}

bool PushBit(BitArray* bitArray, Bit bit){
	if (bitArray->Count >= bitArray->MaxCount){
		return False;
	}
	//Set the pushed bit.
	SetBit(bitArray, bitArray->Count, bit);
	return True;
}

/*
Pushes a splice of a byte onto the bit array.
the first bit from the left is treated as index 0.
Pushed bits will be inclusive of fromIndex and exclusive of upToIndex.
*/
size_t PushByteSlice(BitArray* bitArray, uint8_t byte, uint8_t fromIndex, uint8_t upToIndex){
	size_t bitsAppended = 0;	
	for (uint8_t i = fromIndex; i < upToIndex; i++){
		if (i >= 0 && i < BITS_IN_BYTE){
			Bit bit = BIT0;
			if ((byte & (1 << (BITS_IN_BYTE - 1 - i))) > 0){
				bit = BIT1;
			}
			if (PushBit(bitArray, bit) == True){
				bitsAppended += 1;
			}
		}
	}
	return bitsAppended;
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

void Clear(BitArray* bitArray){
	for (size_t i = 0; i < BytesForBits(bitArray->MaxCount); ++i)
	{
		bitArray->Bits[i] = 0x00;
	}
	bitArray->Count = 0;
}

size_t Append(BitArray* original, BitArray* appendBits){
	size_t bitsAppended = 0;
	for (size_t i = 0; i < appendBits->Count; i++){
		Bit bit = GetBit(appendBits, i);
		if (PushBit(original, bit) == False){
			return bitsAppended;
		}
		bitsAppended += 1;
	}
	return bitsAppended;
}

size_t BytesForBits(size_t bits){
	size_t bytes = bits / BITS_IN_BYTE;
	if (bits % BITS_IN_BYTE != 0){
		bytes += 1;
	}
	return bytes;
}

/*
==============================================================
					Private Methods
==============================================================
*/

size_t BitsInBytes(size_t bytes){
	return bytes * BITS_IN_BYTE;
}

size_t ByteIndex(size_t forBit){
	return forBit / BITS_IN_BYTE;
}

uint8_t ShiftForBit(size_t forBit){
	return (BITS_IN_BYTE - ((forBit + 1) % BITS_IN_BYTE)) % BITS_IN_BYTE;
}