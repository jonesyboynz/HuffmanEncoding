#include "FileStream.h"

#define FILE_STREAM_BUFFER_LENGTH 1024

void FlushBuffer(FileStream* stream);

FileStream* NewFileStream(FILE* file){
	FileStream* stream = calloc(1, sizeof(FileStream));
	stream->File = file;
	stream->Buffer = NewBitArray(FILE_STREAM_BUFFER_LENGTH * BITS_IN_BYTE);
	return stream;
}

void DestroyFileStream(FileStream* stream){
	Destroy(stream->Buffer);
	free(stream);
}

void PushBits(FileStream* stream, BitArray* bitArray){
	size_t bitsAppended = Append(stream->Buffer, bitArray);
	if (bitsAppended == bitArray->Count){
		return;
	}
	//Was not able to write all bits. Need to clear the buffer and try again.
	for (size_t i = bitsAppended; i < bitArray->Count; i++){
		if (PushBit(stream->Buffer, GetBit(bitArray, i)) == False){
			FlushBuffer(stream);
			PushBit(stream->Buffer, GetBit(bitArray, i));
		}
	}
}

//Fill up the current byte and writes the buffer.
void FinishOutput(FileStream* stream){
	while (stream->Buffer->Count % BITS_IN_BYTE != 0){
		PushBits(stream, BIT0);
	}
	FlushBuffer(stream);
}

//======================================================
//					PRIVATE METHODS
//======================================================

void FlushBuffer(FileStream* stream){
	//Write the buffer to the file and then reset it.
	fwrite(stream->Buffer->Bits, sizeof(Bit), BytesForBits(stream->Buffer->Count), stream->File);
	Clear(stream->Buffer);	
}