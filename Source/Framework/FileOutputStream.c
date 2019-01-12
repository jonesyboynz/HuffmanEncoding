#include "FileOutputStream.h"

#define FILE_STREAM_BUFFER_LENGTH 1024

void FlushBuffer(FileOutputStream* stream);

FileOutputStream* NewFileOutputStream(FILE* file){
	FileOutputStream* stream = calloc(1, sizeof(FileOutputStream));
	stream->File = file;
	stream->Buffer = NewBitArray(FILE_STREAM_BUFFER_LENGTH * BITS_IN_BYTE);
	return stream;
}

void DestroyFileOutputStream(FileOutputStream* stream){
	Destroy(stream->Buffer);
	fclose(stream->File);
	free(stream);
}

void PushBits(FileOutputStream* stream, BitArray* bitArray){
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
void FinishOutput(FileOutputStream* stream){
	while (stream->Buffer->Count % BITS_IN_BYTE != 0){
		PushBit(stream->Buffer, BIT0);
	}
	FlushBuffer(stream);
}

//======================================================
//					PRIVATE METHODS
//======================================================

void FlushBuffer(FileOutputStream* stream){
	//Write the buffer to the file and then reset it.
	fwrite(stream->Buffer->Bits, sizeof(Bit), BytesForBits(stream->Buffer->Count), stream->File);
	Clear(stream->Buffer);	
}