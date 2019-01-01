#include "HuffTree.h"
#include "SymbolTable.h"

void AddSymbolToTable(SymbolTable* table, HuffNode* node, BitArray* bitArray);

//Converts a tree to a heap.
void GenerateTreeWithinHeap(HuffHeap* heap){
	while(heap->Count > 1){
		HuffNode* left_node = Remove(heap);
		HuffNode* right_node = Remove(heap);
		HuffNode* parentNode = NewHuffNode(0x00, left_node->Freq + right_node->Freq);
		parentNode->Left = left_node;
		parentNode->Right = right_node;
		Add(heap, parentNode);
	}
}

//Gets the number of nodes within a tree.
uint16_t Count(HuffNode* node){
	if (node == NULL){
		return 0;
	}
	return 1 + Count(node->Left) + Count(node->Right);
}

//gets the number of lead nodes within a tree.
uint16_t LeafCount(HuffNode* node){
	if (node == NULL){
		return 0;
	}
	if (IsLeaf(node)){
		return 1;
	}
	return LeafCount(node->Left) + LeafCount(node->Right);
}

SymbolTable* GenerateEncodingSymbols(HuffNode* node){
	SymbolTable* table = NewSymbolTable();
	BitArray* bitArray = NewBitArray(SYSTEM_SYMBOL_MAX_BITS);
	AddSymbolToTable(table, node, bitArray);
	return table;
}

//=============================================================================
//							PRIVATE METHODS
//=============================================================================

//Recursively adds symbols to the table
void AddSymbolToTable(SymbolTable* table, HuffNode* node, BitArray* bitArray){
	if (IsLeaf(node) == True){
		//Add symbol.
		Symbol* symbol = NewSymbol(node->Character, Copy(bitArray));
		table->Table[node->Character] = symbol;
	}
	if (node->Left != NULL){
		PushBit(bitArray, BIT0);
		AddSymbolToTable(table, node->Left, bitArray);
		PopBit(bitArray);
	}
	if (node->Right != NULL){
		PushBit(bitArray, BIT1);
		AddSymbolToTable(table, node->Right, bitArray);
		PopBit(bitArray);
	}
}