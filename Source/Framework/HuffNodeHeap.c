#include "HuffNodeHeap.h"

uint16_t ParentIndex(uint16_t index);

uint16_t LeftChild(uint16_t index);

uint16_t RightChild(uint16_t index);

void Swap(HuffHeap* heap, uint16_t index1, uint16_t index2);

void FlowUp(HuffHeap* heap, uint16_t index);

void FlowDown(HuffHeap* heap, uint16_t index);

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

void DestroyHeapAndAllNodes(HuffHeap* heap){
	for (uint16_t i = HEAP_ROOT_INDEX; i < heap->Count + HEAP_ROOT_INDEX; i++){
		//Careful. Nodes could be linked here.
		Destory(heap->Heap[i]);
	}
	free(heap);
}

HuffNode* Remove(HuffHeap* heap){
	if (heap->Count < 1){
		return NULL;
	}
	HuffNode* returnNode = heap->Heap[HEAP_ROOT_INDEX];
	heap->Heap[HEAP_ROOT_INDEX] = heap->Heap[heap->Count];
	heap->Count -= 1;
	if (heap->Count > 1){
		FlowDown(heap, HEAP_ROOT_INDEX);
	}
	return returnNode;
}

/*
==================================================================================
								PRIVATE METHODS
==================================================================================
*/

uint16_t Parent(uint16_t index){
	return index / 2;
}

uint16_t LeftChild(uint16_t index){
	return index * 2;
}

uint16_t RightChild(uint16_t index){
	return index * 2 + 1;
}

void Swap(HuffHeap* heap, uint16_t index1, uint16_t index2){
	HuffNode* temp = heap->Heap[index1];
	heap->Heap[index1] = heap->Heap[index2];
	heap->Heap[index2] = temp;
}

void FlowUp(HuffHeap* heap, uint16_t index){
	uint16_t parentIndex = Parent(index);
	if (index > heap->Count || index == 0 || parentIndex == 0){
		return;
	}
	if (heap->Heap[index]->Freq < heap->Heap[parentIndex]->Freq){
		Swap(heap, index, parentIndex);
	}
	if (parentIndex > HEAP_ROOT_INDEX){
		FlowUp(heap, parentIndex);
	}
}

void FlowDown(HuffHeap* heap, uint16_t index){
	uint16_t left = LeftChild(index);
	uint16_t right = RightChild(index);
	//No right or left child.
	if (left > heap->Count && right > heap->Count){
		return;
	}
	//No right child, check left child.
	if (right > heap->Count && heap->Heap[left]->Freq < heap->Heap[index]->Freq){
		Swap(heap, index, left);
		return;
	}
	//Right and left child.
	if (heap->Heap[left]->Freq < heap->Heap[index]->Freq || heap->Heap[right]->Freq < heap->Heap[index]->Freq){
		if (heap->Heap[left]->Freq <= heap->Heap[right]->Freq){
			Swap(heap, index, left);
			FlowDown(heap, left);
		}
		else{
			Swap(heap, index, right);
			FlowDown(heap, right);
		}
	}
}
