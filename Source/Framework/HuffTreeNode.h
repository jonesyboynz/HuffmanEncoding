/*
Node for the huffman tree
*/

#ifndef HUFF_TREE_NODE_H
#define HUFF_TREE_NODE_H

#include "CoreIncludes.h"

typedef struct huff_node_s HuffNode;

struct huff_node_s {
	uint8_t Character;
	uint32_t Frequency;
	HuffNode* Left;
	HuffNode* Right;
};

HuffNode* NewHuffNode(uint8_t character, uint32_t frequency);

bool IsLeaf(HuffNode* node);

#endif