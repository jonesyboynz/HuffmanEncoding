#include "HuffTree.h"
#include "SymbolTable.h"

#include "Debug.h"

void AddSymbolToTable(SymbolTable* table, HuffNode* node, BitArray* bitArray);

void AddSymbolToTree(Symbol* symbol, HuffNode* parent, uint16_t current_index, bool is_eof);

//Converts a heap to a tree.
void GenerateTreeWithinHeap(HuffHeap* heap){
	while(heap->Count > 1){
		HuffNode* left_node = Remove(heap);
		HuffNode* right_node = Remove(heap);
		HuffNode* parentNode = NewHuffNode(BYTE_UNUSED, SYMBOL_TYPE_PARENT, left_node->Freq + right_node->Freq);
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


HuffNode* GenerateTreeFromTable(SymbolTable* table){
	HuffNode* root = NewHuffNode(BYTE_UNUSED, SYMBOL_TYPE_PARENT, 0);
	for (uint16_t i = 0; i < SYSTEM_SYMBOL_COUNT; i++)
	{
		if (table->Table[i] != NULL){
			AddSymbolToTree(table->Table[i], root, 0, (i == EOF_CHARACTER_VALUE) ? True : False);
		}
	}
	return root;
}

//=============================================================================
//							PRIVATE METHODS
//=============================================================================

//Recursively adds symbols to the table
void AddSymbolToTable(SymbolTable* table, HuffNode* node, BitArray* bitArray){
	if (IsLeaf(node) == True){
		//Add symbol.
		Symbol* symbol = NewSymbol(node->Character, Copy(bitArray));
		if (node->Type == SYMBOL_TYOE_EOF){
			table->Table[EOF_CHARACTER_VALUE] = symbol;
		}
		else{
			table->Table[node->Character] = symbol;
		}	
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

//Adds a symbol to the tree
void AddSymbolToTree(Symbol* symbol, HuffNode* parent, uint16_t current_index, bool is_eof){
	Bit current_bit = GetBit(symbol->BitArray, current_index);
	if (current_bit == BIT0){
		if (current_index == symbol->BitArray->Count - 1){
			parent->Left = NewHuffNode(symbol->Character, (is_eof) ? SYMBOL_TYOE_EOF : SYMBOL_TYPE_CHARACTER, 0);
			return;
		}
		else if (parent->Left == NULL){
			parent->Left = NewHuffNode(BYTE_UNUSED, SYMBOL_TYPE_PARENT, 0);
		}
		AddSymbolToTree(symbol, parent->Left, current_index + 1, is_eof);
	}
	else{
		if (current_index == symbol->BitArray->Count - 1){
			parent->Right = NewHuffNode(symbol->Character, (is_eof) ? SYMBOL_TYOE_EOF : SYMBOL_TYPE_CHARACTER, 0);
			return;
		}
		else if (parent->Right == NULL){
			parent->Right = NewHuffNode(BYTE_UNUSED, SYMBOL_TYPE_PARENT, 0);
		}
		AddSymbolToTree(symbol, parent->Right, current_index + 1, is_eof);
	}
}

bool ValidateTree(HuffNode* node){
	if (node->Type == SYMBOL_TYPE_PARENT){
		if (node->Left == NULL || node->Right == NULL){
			return False;
		}
		return ValidateTree(node->Left) && ValidateTree(node->Right);
	}
	if (node->Left == NULL && node->Right == NULL){
		return True;
	}
	return False;
}