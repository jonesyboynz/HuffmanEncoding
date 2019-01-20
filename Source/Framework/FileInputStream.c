#include "FileInputStream.h"

void GetNextBytes(FileInputStream* stream);

FileInputStream* NewFileInputStream(FILE* file){
	FileInputStream* stream = malloc(sizeof(FileInputStream));
	stream->File = file;
	stream->Buffer = NewBitArray(FILE_STREAM_BUFFER_LENGTH * BITS_IN_BYTE);
	stream->EndOfFile = False;
	return stream;
}

void DestoryFileInputStream(FileInputStream* stream){
	fclose(stream->File);
	Destroy(stream->Buffer);
	free(stream);
}

size_t ShiftBitsTo(FileInputStream* stream, uint32_t* value, size_t bits){
	size_t count = 0;
	while (count < bits && stream->EndOfFile == False){
		if (stream->Buffer->Count > 0){
			Bit bit = PopBit(stream->Buffer);
			*value = (*value << 1) + bit;
			count += 1;
		}
		else{
			GetNextBytes(stream);
		}
	}
	return count;
}

BitArray* ShiftBitsToArray(FileInputStream* stream, size_t bits){
	BitArray* array = NewBitArray(bits);
	size_t count = 0;
	while (count < bits && stream->EndOfFile == False){
		if (stream->Buffer->Count > 0){
			PushBit(array, PopBit(stream->Buffer));
		}
		else{
			GetNextBytes(stream);
		}
	}
	return array;
}

//=========================================================================
//							PRIVATE METHODS
//=========================================================================

void GetNextBytes(FileInputStream* stream){
	size_t bytes_read = fread(stream->Buffer->Bits, sizeof(uint8_t), FILE_STREAM_BUFFER_LENGTH, stream->File);
	stream->Buffer->Count = bytes_read * BITS_IN_BYTE;
	if (bytes_read == 0){
		stream->EndOfFile = True;
	}	
}