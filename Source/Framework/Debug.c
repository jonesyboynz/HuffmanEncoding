#include "Debug.h"
#include <inttypes.h>

//Private
void HandleNewLine(DebugDisplayOptions option);

//Private
void HandleFinalActions(DebugDisplayOptions option);

//Private
void Repeat(uint8_t character, uint16_t times);

//Private
void DisplayHuffTree_Rec(HuffNode* node, uint16_t depth);

void DisplayBinary(uint8_t byte, DebugDisplayOptions option){
	for(uint8_t i = 0; i < BITS_IN_BYTE; i++){
		uint8_t mask = 1 << (BITS_IN_BYTE - 1 - i);
		if ((byte & mask) > 0){
			printf("1");
		}
		else{
			printf("0");
		}
	}
	HandleFinalActions(option);
}

void DisplayHuffHeap(HuffHeap* heap, DebugDisplayOptions option){
	printf("Heap[%p,\n", heap);
	for (uint16_t i = HEAP_ROOT_INDEX; i < heap->Count + HEAP_ROOT_INDEX; i++){
		DisplayHuffNode(heap->Heap[i], DISPLAY_OPTION_NO_FLUSH);
	}
	printf("]");
	HandleFinalActions(option);
}

void DisplayFrequencyTable(Frequency* frequencies, DebugDisplayOptions option){
	printf("FrequencyTable[%p,\n", frequencies);
	for (uint16_t i = 0; i < SYSTEM_SYMBOL_COUNT; i++){
		if (frequencies[i] == 0 && (option & DISPLAY_OPTION_EXPLICIT) > 0){
			printf("C(%02x, %c): 0\n", i, i);
		}
		else if (frequencies[i] > 0){
			printf("C(%02x, %c): %" PRId64 "\n", i, i, ((uint64_t) frequencies[i]));
		}
	}
	printf("]");
	HandleFinalActions(option);
}

void DisplayHuffTree(HuffNode* root, DebugDisplayOptions option){
	printf("Tree[%p\n", root);
	DisplayHuffTree_Rec(root, 0);
	printf("]");
	HandleFinalActions(option);
}

void DisplayBitArray(BitArray* array, DebugDisplayOptions option){
	printf("BitArray[%zd, %zd, ", array->MaxCount, array->Count);
	for (size_t i = 0; i < BytesForBits(array->Count); i++){
		DisplayBinary(array->Bits[i], DISPLAY_OPTION_NO_NEWLINE | DISPLAY_OPTION_NO_FLUSH);
	}
	printf("]");
	HandleFinalActions(option);
}

void DisplayHuffNode(HuffNode* node, DebugDisplayOptions option){
	printf("Node[%p, %c, %" PRId64 ", *L:%p, *R:%p]",
		node,
		node->Character,
		((uint64_t) node->Freq),
		node->Left,
		node->Right);
	HandleFinalActions(option);
}

void DisplaySymbolTable(SymbolTable* table, DebugDisplayOptions option){
	printf("SymbolTable[%p,\n", table);
	for (uint16_t i = 0; i < SYSTEM_SYMBOL_COUNT; i++){
		Symbol* currentSymbol = table->Table[i];
		if ((option & DISPLAY_OPTION_EXPLICIT) > 0 && currentSymbol == NULL){
			printf("%d, NULL\n", i);
		}
		else if (currentSymbol != NULL){
			printf("%d, ", i);
			DisplaySymbol(currentSymbol, DISPLAY_OPTION_NO_FLUSH);
		}
	}
	printf("]");
	HandleFinalActions(option);
}

void DisplaySymbol(Symbol* symbol, DebugDisplayOptions option){
	printf("Symbol[%c, ", symbol->Character);
	DisplayBitArray(symbol->BitArray, DISPLAY_OPTION_NO_NEWLINE | DISPLAY_OPTION_NO_FLUSH);
	printf("]");
	HandleFinalActions(option);
}

//=============================================================
//						PRIVATE METHODS
//=============================================================

void HandleNewLine(DebugDisplayOptions option){
	if ((option & DISPLAY_OPTION_NO_NEWLINE) > 0){
		return;
	}
	else{
		printf("\n");
	}
}

void HandleFinalActions(DebugDisplayOptions option){
	HandleNewLine(option);
	if ((option & DISPLAY_OPTION_NO_FLUSH) == 0){
		fflush(NULL);
	}
}

void Repeat(uint8_t character, uint16_t times){
	for (uint16_t i = 0; i < times; ++i)
	{
		printf("%c", character);
	}
}

void DisplayHuffTree_Rec(HuffNode* node, uint16_t depth){
	if (node == NULL){
		return;
	}
	Repeat('\t', depth);
	DisplayHuffNode(node, DISPLAY_OPTION_NO_FLUSH);
	DisplayHuffTree_Rec(node->Left, depth + 1);
	DisplayHuffTree_Rec(node->Right, depth + 1);
}
