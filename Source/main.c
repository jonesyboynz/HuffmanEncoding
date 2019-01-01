#include <stdio.h>
#include <stdlib.h>
#include "Framework/Framework.h"
#include "Encoding/CharacterFrequencies.h"


int main(int argc, char **argv){
	if (argc != 2 && argc != 3){
		UsageMessage();
		return EXIT_FAIL;
	}

	FILE* input;
	FILE* output;
	char* inputFilename;
	char* outputFilename;

	//Open input file.
	inputFilename = argv[1];
	input = fopen(inputFilename, "rb");

	//Check the input file.
	if (ferror(input) != 0){
		UnableToOpenInputMessage(inputFilename);
		return EXIT_FAIL;
	}

	//Open output file.
	if(argc == 3){
		outputFilename = argv[2];
		output = fopen(outputFilename, "wb");
	}
	else{
		//TODO : needs a custom file name.
		//output = fopen(SomeFunction(argv[2]), "wb");
		return EXIT_FAIL;
	}

	//Check the output file.
	if (ferror(output) != 0){
		UnableToOpenOutputMessage(outputFilename);
		fclose(input);
		return EXIT_FAIL;
	}

	//Character frequencies
	Frequency* frequencies = CharacterFrequency(input);

	//Get heap
	HuffHeap* heap = GetHeapFromFrequencies(frequencies);

	//Create huffman tree.
	GenerateTreeWithinHeap(heap);

	//get symbol table 
	SymbolTable* table = GenerateEncodingSymbols(heap->Heap[HEAP_ROOT_INDEX]);
	DISPLAY_SYMBOL_TABLE_DEF(table);

	//convert file to symbols & write

	printf("DONE!\n");

	//Cleanup
	fclose(input);
	fclose(output);
	free(frequencies);
	DestroyHeapAndAllNodes(heap);
	DestroySymbolTable(table);

	return EXIT_SUCCESS;
}