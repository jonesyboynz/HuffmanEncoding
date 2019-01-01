#include "ByteArray.h"
#include  <string.h>

ByteArray* NewByteArray(size_t length){
	ByteArray* array = calloc(1, sizeof(ByteArray));
	uint8_t* data = calloc(length, sizeof(uint8_t));
	array->Data = data;
	array->MaxCount = length;
	return array;
}

void DestroyByteArray(ByteArray* byteArray){
	free(byteArray->Data);
	free(byteArray);
}

bool PushByte(ByteArray* byteArray, uint8_t byte){
	if (byteArray->Count >= byteArray->MaxCount){
		return False;
	}
	byteArray->Data[byteArray->Count] = byte;
	byteArray->Count += 1;
	return True;
}

uint8_t PopByte(ByteArray* byteArray){
	if (byteArray->Count == 0){
		return BYTE_ERROR; //Still returns a byte though...
	}
	uint8_t returnValue = byteArray->Data[byteArray->Count - 1];
	byteArray->Count -= 1;
	return returnValue;
}

ByteArray* Union(ByteArray* byteArray1, ByteArray* byteArray2){
	ByteArray* unionArray = NewByteArray(byteArray1->MaxCount + byteArray2->MaxCount);
	if (byteArray1->Count > 0){
		memcpy(unionArray->Data, byteArray1->Data, byteArray1->Count);
		unionArray->Count += byteArray1->Count;
	}
	if (byteArray2->Count > 0){
		memcpy(&(unionArray->Data[unionArray->Count]), byteArray2->Data, byteArray2->Count);
		unionArray->Count += byteArray2->Count;
	}
	return unionArray;
}