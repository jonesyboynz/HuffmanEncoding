#include <stdio.h>
#include <stdlib.h>
#include "Test.h"
#include "../../../Source/Framework/HuffTreeNode.h"
#include "../../Framework/Framework.h"

bool Is_leaf_test1();

bool Is_leaf_test2();

TestSet* Huffman_tree_test_set(){
	TestSet* set = NewTestSet("Huffman tree node");
	AddTest(set, NewTest("Is leaf works on leaf nodes", Is_leaf_test1, False));
	AddTest(set, NewTest("Is leaf works on parent nodes", Is_leaf_test2, False));
	return set;
}

bool Is_leaf_test1(){
	HuffNode* node = NewHuffNode(0x48, 1);
	return AssertTrue(IsLeaf(node));
}

bool Is_leaf_test2(){
	HuffNode* node1 = NewHuffNode(0x48, 1);
	HuffNode* node2 = NewHuffNode(0x48, 1);
	node1->Left=node2;
	return AssertFalse(IsLeaf(node1));
}
