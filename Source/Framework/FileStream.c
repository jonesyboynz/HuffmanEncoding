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

void PushBits(BitArray* bitArray){

}

//======================================================
//					PRIVATE METHODS
//======================================================

void FlushBuffer(FileStream* stream){
	//Write the buffer to the file and
	fwrite(stream->Buffer->Bits, sizeof(Bit), BytesForBits(stream->Buffer->Count), stream->File);
	Clear(stream->Buffer);	
}