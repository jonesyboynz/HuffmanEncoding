#include "Messages.h"

void UsageMessage(){
	printf("Usage: huff [required:input_file] [optional:output_file]\n");
}

void UnableToOpenInputMessage(char* filename){
	printf("Error: Unable to read from input file \"%s\". Does it exist?\n", filename);
}

void UnableToOpenOutputMessage(char* filename){
	printf("Error: Unable to write to output file \"%s\". Is it currently open?\n", filename);
}
