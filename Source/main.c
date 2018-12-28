#include <stdio.h>
#include <stdlib.h>
#include "Framework/Framework.h"


int main(int argc, char **argv){
	if (argc != 2 && argc != 3){
		UsageMessage();
		return EXIT_FAIL;
	}

	FILE* input;
	FILE* output;

	//Open input file.
	input = fopen(argv[1], "rb");

	//Check the input file.
	if (ferror(input) != 0){
		return EXIT_FAIL;
	}

	//Open output file.
	if(argc == 3){
		output = fopen(argv[2], "wb");
	}
	else{
		//TODO : needs a custom file name.
		//output = fopen(SomeFunction(argv[2]), "wb");
		return EXIT_FAIL;
	}

	//Check the output file.
	if (ferror(output) != 0){
		fclose(input);
		return EXIT_FAIL;
	}

	//character frequencies

	//get heap

	//get symbols

	//convert symbols to table & write

	//convert file to symbols & write

	printf("DONE!\n");

	//Cleanup
	fclose(input);
	fclose(output);

	return EXIT_SUCCESS;
}