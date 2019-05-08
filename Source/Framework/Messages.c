#include "Messages.h"

void UsageMessage(){
	printf("Usage: huff [encode|decode|e|d] [required:input_file] [optional:output_file]\n");
}

void UnableToOpenInputMessage(char* filename){
	printf("Error: Unable to read from input file \"%s\". Does it exist?\n", filename);
}

void UnableToOpenOutputMessage(char* filename){
	printf("Error: Unable to write to output file \"%s\". Is it currently open?\n", filename);
}

void ModeInvalidMessage(char* mode){
	printf("Error: Invalid mode \"%s\". Mode should be [encode|decode|e|d]\n", mode);
}

void DecodingError(char* message){
	printf("Decoding Error: %s\n", message);
}
