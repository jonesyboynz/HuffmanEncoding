#include "HuffTreeNode.h"

HuffNode* NewHuffNode(uint8_t character, uint8_t type, Frequency frequency){
	HuffNode* newNode = calloc(1, sizeof(HuffNode));
	newNode->Character = character;
	newNode->Freq = frequency;
	newNode->Type = type;
	return newNode;
}

bool IsLeaf(HuffNode* node){
	if (node->Left == NULL && node->Right == NULL){
		return True;
	}
	return False;
}

void Destory(HuffNode* node){
	if (node->Left != NULL){
		Destory(node->Left);
	}
	if (node->Right != NULL){
		Destory(node->Right);
	}
	free(node);
}