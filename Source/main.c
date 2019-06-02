#include "Framework/Framework.h"
#include "Encoding/Encode.h"
#include "Decoding/Decode.h"

#define MAX_ARGUMENT_LENGTH 1024

#define ARGUMENT_MODE_POSITION 1
#define ARGUMENT_INPUT_FILE_POSITION 2
#define ARGUMENT_OUTPUT_FILE_POSITION 3

//TODO : These methods could live elsewhere methinks.

char* GenerateFilename(char* baseName, Mode mode){
	char* buffer = calloc(1024, sizeof(char));
	size_t baseNameLength = strnlen(baseName, 1024);
	strncpy(buffer, baseName, baseNameLength);
	if (mode == MODE_ENCODE){
		strncpy(buffer + baseNameLength, ".encoded", 1024 - baseNameLength);
	}	
	else{
		strncpy(buffer + baseNameLength, ".decoded", 1024 - baseNameLength);
	}
	
	buffer[MAX_ARGUMENT_LENGTH - 1] = 0x00; //Ensure null termination.

	printf("Generated output filename: %s\n", buffer);

	return buffer;
}


Mode GetMode(char* modeArgument){
	size_t length = strnlen(modeArgument, MAX_ARGUMENT_LENGTH);
	if (length == 1){
		switch (modeArgument[0]){
			case 'e':
				return MODE_ENCODE;
			case 'd':
				return MODE_DECODE;
			default:
				return MODE_INVALID;
		}
	}
	if (strncmp(modeArgument, "encode", MAX_ARGUMENT_LENGTH) == 0){
		return MODE_ENCODE;
	}
	if (strncmp(modeArgument, "decode", MAX_ARGUMENT_LENGTH) == 0){
		return MODE_DECODE;
	}
	return MODE_INVALID;
}


int main(int argc, char **argv){
	Mode mode;
	FILE* input;
	FILE* output;
	char* inputFilename;
	char* outputFilename;
	char* generatedFilename = NULL;
	FileOutputStream* outputStream;

	if (argc < 3 || argc > 4){
		UsageMessage();
		return EXIT_FAIL;
	}

	mode = GetMode(argv[ARGUMENT_MODE_POSITION]);
	if (mode == MODE_INVALID){
		ModeInvalidMessage(argv[ARGUMENT_MODE_POSITION]);
		return EXIT_FAIL;
	}

	//Open input file.
	inputFilename = argv[ARGUMENT_INPUT_FILE_POSITION];
	input = fopen(inputFilename, "rb");

	//Check the input file.
	if (ferror(input) != 0){ 
		UnableToOpenInputMessage(inputFilename);
		return EXIT_FAIL;
	}

	//Open output file.
	if(argc == 4){
		outputFilename = argv[ARGUMENT_OUTPUT_FILE_POSITION];
		output = fopen(outputFilename, "wb");
	}
	else{
		generatedFilename = GenerateFilename(inputFilename, mode);
		output = fopen(generatedFilename, "wb");
	}

	//Check the output file.
	if (ferror(output) != 0){
		UnableToOpenOutputMessage(outputFilename);
		fclose(input);
		return EXIT_FAIL;
	}

	//Create file streams.
	outputStream = NewFileOutputStream(output);

	//Conditional logic for encode/decode here.
	if (mode == MODE_ENCODE){
		//Encode the symbol table and file. Write to file.
		Encode(input, outputStream);
	}
	else { //Must be decode mode
		Decode(input, outputStream);
	} 

	//Cleanup
	DestroyFileOutputStream(outputStream);
	fclose(input);

	if (generatedFilename != NULL){
		free(generatedFilename);
	}

	return EXIT_SUCCESS;
}