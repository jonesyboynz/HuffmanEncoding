#include "Test.h"
#include "../../Framework/Framework.h"
#include "../../../Source/Encoding/CharacterFrequencies.h"
#include "../../../Source/Decoding/Deserializer.h"

bool Is_leaf_test1();

bool Is_leaf_test2();

bool Can_generate_tree_test();

bool Tree_structure_is_correct_test();

bool Tree_count_is_correct_test();

bool Tree_frequency_is_correct_test();

bool Can_validate_valid_tree_test();

bool Can_invalidate_invalid_tree_test();

TestSet* Huffman_node_test_set();

TestSet* Huffman_tree_test_set();

TestSet* Huffman_tree_test_sets(){
	TestSet* set = NewTestSet("Huffman tree tests");
	AddChildTestSet(set, Huffman_node_test_set());
	AddChildTestSet(set, Huffman_tree_test_set());
	return set;
}

TestSet* Huffman_tree_test_set(){
	TestSet* set = NewTestSet("Tree tests");
	AddTest(set, NewTest("Can create tree", Can_generate_tree_test, False));
	AddTest(set, NewTest("Tree structure is correct", Tree_structure_is_correct_test, False));
	AddTest(set, NewTest("Tree frequency is correct", Tree_frequency_is_correct_test, False));
	AddTest(set, NewTest("Tree count is correct", Tree_count_is_correct_test, False));
	AddTest(set, NewTest("Can detect valid trees", Can_validate_valid_tree_test, False));
	AddTest(set, NewTest("Can detect invalid trees", Can_invalidate_invalid_tree_test, False));
	return set;	
}

TestSet* Huffman_node_test_set(){
	TestSet* set = NewTestSet("Node tests");
	AddTest(set, NewTest("Is leaf works on leaf nodes", Is_leaf_test1, False));
	AddTest(set, NewTest("Is leaf works on parent nodes", Is_leaf_test2, False));
	return set;	
}

bool Is_leaf_test1(){
	HuffNode* node = NewHuffNode(0x48, SYMBOL_TYPE_CHARACTER, 1);
	return AssertTrue(IsLeaf(node));
}

bool Is_leaf_test2(){
	HuffNode* node1 = NewHuffNode(0x48, SYMBOL_TYPE_CHARACTER, 1);
	HuffNode* node2 = NewHuffNode(0x48, SYMBOL_TYPE_CHARACTER, 1);
	node1->Left=node2;
	return AssertFalse(IsLeaf(node1));
}

bool Can_generate_tree_test(){
	FILE* file = fopen("Test/Data/frequency_test1", "rb");
	Frequency* frequencies = CharacterFrequency(file);
	HuffHeap* heap = GetHeapFromFrequencies(frequencies);
	bool result = AssertEquals(heap->Count, 6);
	GenerateTreeWithinHeap(heap);
	result &= AssertEquals(heap->Count, 1);
	DestroyHeapAndAllNodes(heap);
	return result;
}

bool Tree_structure_is_correct_test(){
	FILE* file = fopen("Test/Data/tree_test_data", "rb");
	Frequency* frequencies = CharacterFrequency(file);
	HuffHeap* heap = GetHeapFromFrequencies(frequencies);
	GenerateTreeWithinHeap(heap);
	bool result = AssertEquals(heap->Count, 1);
	result &= AssertEquals(heap->Heap[1]->Right->Right->Right->Character, 'a');
	result &= AssertEquals(heap->Heap[1]->Right->Left->Character, 'b');
	result &= AssertEquals(heap->Heap[1]->Left->Character, 'c');
	DestroyHeapAndAllNodes(heap);
	return result;
}

bool Tree_frequency_is_correct_test(){
	FILE* file = fopen("Test/Data/tree_test_data", "rb");
	Frequency* frequencies = CharacterFrequency(file);
	HuffHeap* heap = GetHeapFromFrequencies(frequencies);
	GenerateTreeWithinHeap(heap);
	bool result = AssertEquals(heap->Count, 1);
	result &= AssertEquals(heap->Heap[1]->Freq, 12);
	result &= AssertEquals(heap->Heap[1]->Right->Freq, 6);
	DestroyHeapAndAllNodes(heap);
	return result;
}

bool Tree_count_is_correct_test(){
	FILE* file = fopen("Test/Data/tree_test_data", "rb");
	Frequency* frequencies = CharacterFrequency(file);
	HuffHeap* heap = GetHeapFromFrequencies(frequencies);
	GenerateTreeWithinHeap(heap);
	bool result = AssertEquals(Count(heap->Heap[1]), 7);
	result = AssertEquals(LeafCount(heap->Heap[1]), 4);
	DestroyHeapAndAllNodes(heap);
	return result;	
}

bool Can_validate_valid_tree_test(){
	HuffNode* node1 = NewHuffNode(0x01, SYMBOL_TYPE_PARENT, 1);
	HuffNode* node2 = NewHuffNode(0x02, SYMBOL_TYPE_CHARACTER, 1);
	HuffNode* node3 = NewHuffNode(0x03, SYMBOL_TYPE_CHARACTER, 1);
	node1->Left=node2;
	node1->Right=node3;
	return AssertTrue(ValidateTree(node1));	
}

bool Can_invalidate_invalid_tree_test(){
	HuffNode* node1 = NewHuffNode(0x01, SYMBOL_TYPE_PARENT, 1);
	HuffNode* node2 = NewHuffNode(0x02, SYMBOL_TYPE_CHARACTER, 1);
	HuffNode* node3 = NewHuffNode(0x03, SYMBOL_TYPE_PARENT, 1);
	HuffNode* node4 = NewHuffNode(0x04, SYMBOL_TYPE_CHARACTER, 1);
	node1->Left=node2;
	node1->Right=node3;
	node1->Right->Left=node4;
	return AssertFalse(ValidateTree(node1));	
}

