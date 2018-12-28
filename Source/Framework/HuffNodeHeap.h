/*
Huffman node heap
*/

#ifndef HUFF_HEAP_H
#define HUFF_HEAP_H

#include "CoreIncludes.h"
#include "HuffTreeNode.h"

#define HEAP_ROOT_INDEX 1

typedef struct huff_heap_s HuffHeap;

struct huff_heap_s {
	HuffNode* Heap[SYSTEM_SYMBOL_COUNT + 1];
	uint16_t Count;  
};

HuffHeap* NewHuffHeap();

bool Add(HuffHeap* heap, HuffNode* node);

void FlowUp(HuffHeap* heap, uint16_t index);

void DestroyHeapAndAllNodes(HuffHeap* heap);

#endif