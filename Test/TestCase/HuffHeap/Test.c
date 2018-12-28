#include <stdio.h>
#include <stdlib.h>
#include "Test.h"
#include "../../../Source/Framework/HuffNodeHeap.h"
#include "../../../Source/Framework/HuffTreeNode.h"
#include "../../Framework/Framework.h"

bool Test_heap_creation();

bool Test_heap_insertion();

bool Test_heap_flow_up();

bool Test_heap_size();

bool Test_heap_max_size();

bool Test_heap_over_size();

TestSet* Huffman_heap_test_set(){
	TestSet* set = NewTestSet("Heap tests");
	AddTest(set, NewTest("Can create heap", Test_heap_creation, False));
	AddTest(set, NewTest("Can insert nodes", Test_heap_insertion, False));
	AddTest(set, NewTest("Nodes re-arrange to maintain heap", Test_heap_flow_up, False));
	AddTest(set, NewTest("Size is correct", Test_heap_size, False));
	AddTest(set, NewTest("Size is correct at the maximum size", Test_heap_max_size, False));
	AddTest(set, NewTest("Size is correct when inserting above maximum size", Test_heap_over_size, False));
	return set;	
}

bool Test_heap_creation(){
	HuffHeap* heap = NewHuffHeap();
	bool result = AssertEquals(heap->Count, 0); 
	free(heap);
	return result;
}

bool Test_heap_insertion(){
	HuffHeap* heap = NewHuffHeap();
	HuffNode* node = NewHuffNode(0x48, 1);
	bool result = Add(heap, node);
	AssertTrue(result);
	result &= AssertEquals(heap->Heap[1]->Character, node->Character);
	free(heap);
	free(node);
	return result;
}

bool Test_heap_flow_up(){
	HuffHeap* heap = NewHuffHeap();
	HuffNode* node1 = NewHuffNode(0x48, 1); //72
	HuffNode* node2 = NewHuffNode(0x49, 2); //73
	HuffNode* node3 = NewHuffNode(0x50, 3); //80
	bool result = Add(heap, node3);
	result &= Add(heap, node2);
	result &= Add(heap, node1);
	result &= AssertTrue(result);
	result &= AssertEquals(heap->Heap[1]->Character, node1->Character);
	result &= AssertEquals(heap->Heap[2]->Character, node3->Character);
	result &= AssertEquals(heap->Heap[3]->Character, node2->Character);
	free(heap);
	free(node1); free(node2); free(node3);
	return result;
}

bool Test_heap_size(){
	HuffHeap* heap = NewHuffHeap();
	HuffNode* node = NewHuffNode(0x48, 1);
	Add(heap, node); Add(heap, node); Add(heap, node);
	Add(heap, node); Add(heap, node); Add(heap, node);
	Add(heap, node); Add(heap, node); Add(heap, node);
	free(heap);
	free(node);
	return AssertEquals(heap->Count, 9);
}

bool Test_heap_max_size(){
	HuffHeap* heap = NewHuffHeap();
	HuffNode* node = NewHuffNode(0x48, 1);
	for (uint16_t i = 0; i < SYSTEM_SYMBOL_COUNT; i++){
		Add(heap, node);
	}
	free(heap);
	free(node);
	return AssertEquals(heap->Count, SYSTEM_SYMBOL_COUNT);
}

bool Test_heap_over_size(){
	HuffHeap* heap = NewHuffHeap();
	HuffNode* node = NewHuffNode(0x48, 1);
	for (uint16_t i = 0; i < SYSTEM_SYMBOL_COUNT; i++){
		Add(heap, node);
	}
	bool result = AssertFalse(Add(heap, node));
	result &= AssertEquals(heap->Count, SYSTEM_SYMBOL_COUNT);
	free(heap);
	free(node);
	return result;
}