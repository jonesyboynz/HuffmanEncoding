#include <stdio.h>
#include <stdlib.h>
#include "AllTestCases.h"
#include "Framework/Framework.h"

bool CanRunFunction(void){
	return True;
}

int main(int argc, char **argv){
	
	//Base test set. Parent to all tests and test sets.
	TestSet* baseTestSet = NewTestSet("Tests");

	//Basic tests.
	TestSet* basicTestSet = NewTestSet("Basic tests");
	Test* basicTest = NewTest("Tests can run", CanRunFunction, False);
	AddTest(basicTestSet, basicTest);
	AddChildTestSet(baseTestSet, basicTestSet);

	//Add framework test sets.
	AddChildTestSet(baseTestSet, Huffman_tree_test_set());
	AddChildTestSet(baseTestSet, Huffman_heap_test_set());

	//Add encoding test sets.
	AddChildTestSet(baseTestSet, Character_frequency_test_set());

	//Run the tests.
	bool result = Execute(baseTestSet);
	DestroyTestSet(baseTestSet);

	//Return
	if (result == False){
		return EXIT_FAIL;
	}
	return EXIT_SUCCESS;
}
