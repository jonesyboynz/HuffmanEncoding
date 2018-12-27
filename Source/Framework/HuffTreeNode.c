#include "HuffTreeNode.h"
#include <stdlib.h>

HuffNode* NewHuffNode(uint8_t character, uint32_t frequency){
	HuffNode* newNode = calloc(1, sizeof(NewHuffNode));
	newNode->Character = character;
	newNode->Frequency = frequency;
	return newNode;
}

bool IsLeaf(HuffNode* node){
	if (node->Left == NULL && node->Right == NULL){
		return True;
	}
	return False;
}