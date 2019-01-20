#include "TestCase/All.h"
#include "Framework/Framework.h"

int main(int argc, char **argv){
	
	//Base test set. Parent to all tests and test sets.
	TestSet* baseTestSet = NewTestSet("All Tests");

	//Framework tests.
	TestSet* frameworkTestSet = NewTestSet("Framework");

	//Encoding tests.
	TestSet* encodingTestSet = NewTestSet("Encoding");

	//Decoding tests.
	TestSet* decodingTestSet = NewTestSet("Decoding");

	AddChildTestSet(baseTestSet, frameworkTestSet);
	AddChildTestSet(baseTestSet, encodingTestSet);
	AddChildTestSet(baseTestSet, decodingTestSet);

	//Add framework test sets.
	AddChildTestSet(frameworkTestSet, Huffman_tree_test_sets());
	AddChildTestSet(frameworkTestSet, Huffman_heap_test_set());
	AddChildTestSet(frameworkTestSet, Bit_array_test_set());
	AddChildTestSet(frameworkTestSet, Symbol_test_set());
	AddChildTestSet(frameworkTestSet, Byte_array_test_set());

	//Add encoding test sets.
	AddChildTestSet(encodingTestSet, Character_frequency_test_set());
	AddChildTestSet(encodingTestSet, Serializer_test_set());

	//Add decoding test sets.
	AddChildTestSet(decodingTestSet, Deserializer_test_set());

	//Run the tests.
	bool result = Execute(baseTestSet);
	DestroyTestSet(baseTestSet);

	//Return
	if (result == False){
		return EXIT_FAIL;
	}
	return EXIT_SUCCESS;
}
