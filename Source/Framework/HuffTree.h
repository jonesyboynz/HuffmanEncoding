/*
Methods for constructing the huffman tree within the heap.
*/

#ifndef HUFF_TREE_H
#define HUFF_TREE_H

#include "HuffNodeHeap.h"

void GenerateTreeWithinHeap(HuffHeap* heap);

uint16_t Count(HuffNode* node);

uint16_t LeafCount(HuffNode* node);

#endif