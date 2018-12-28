#include <stdlib.h>
#include <stdio.h>
#include "HuffNodeHeap.h"

uint16_t ParentIndex(uint16_t index);

void Swap(HuffHeap* heap, uint16_t index1, uint16_t index2);

/*
Note: root index = 1 to simplify the heap algorithm.
*/
HuffHeap* NewHuffHeap(){
	HuffHeap* newHeap = calloc(1, sizeof(HuffHeap));
	return newHeap;
}

bool Add(HuffHeap* heap, HuffNode* node){
	if (heap->Count == SYSTEM_SYMBOL_COUNT){
		return False;
	}
	heap->Heap[heap->Count + HEAP_ROOT_INDEX] = node;
	heap->Count += 1;
	FlowUp(heap, heap->Count);
	return True;
}

void FlowUp(HuffHeap* heap, uint16_t index){
	uint16_t parentIndex = ParentIndex(index);
	if (index > heap->Count || index == 0 || parentIndex == 0){
		return;
	}
	if (heap->Heap[index]->Frequency < heap->Heap[parentIndex]->Frequency){
		Swap(heap, index, parentIndex);
	}
	if (parentIndex > HEAP_ROOT_INDEX){
		FlowUp(heap, parentIndex);
	}
}

void DestroyHeapAndAllNodes(HuffHeap* heap){
	for (uint16_t i = HEAP_ROOT_INDEX; i < heap->Count + HEAP_ROOT_INDEX; i++){
		free(heap->Heap[i]);
	}
	free(heap);
}

/*
==================================================================================
								PRIVATE METHODS
==================================================================================
*/

uint16_t ParentIndex(uint16_t index){
	return index / 2;
}

void Swap(HuffHeap* heap, uint16_t index1, uint16_t index2){
	HuffNode* temp = heap->Heap[index1];
	heap->Heap[index1] = heap->Heap[index2];
	heap->Heap[index2] = temp;
}

