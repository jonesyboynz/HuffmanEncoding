#include "Test.h"
#include "../../../Source/Encoding/Serializer.h"
#include "../../../Source/Encoding/CharacterFrequencies.h"

#define SETUP() SETUP_BASE(); SymbolTable* table = Data_setup(); BitArray* array = SerializeSymbolTable(table)
#define TEARDOWN() DestroySymbolTable(table); Destroy(array); TEARDOWN_BASE()

bool Can_serialize_table_test();

bool Serialized_table_length_is_correct();

bool Symbol_1_is_encoded_correctly();

bool Symbol_2_is_encoded_correctly();

TestSet* Serializer_test_set(){
	TestSet* set = NewTestSet("Serializer tests");
	AddTest(set, NewTest("Can serialize table", Can_serialize_table_test, False));
	AddTest(set, NewTest("Serialized table length is correct", Serialized_table_length_is_correct, False));
	AddTest(set, NewTest("Serialized table byte 1 is correct", Symbol_1_is_encoded_correctly, False));
	AddTest(set, NewTest("Serialized table byte 2 is correct", Symbol_2_is_encoded_correctly, False));
	return set;
}

SymbolTable* Data_setup(){
	FILE* file = fopen("Test/Data/serializer_test_data", "rb");
	Frequency* frequencies = CharacterFrequency(file);
	HuffHeap* heap = GetHeapFromFrequencies(frequencies);
	GenerateTreeWithinHeap(heap);
	SymbolTable* table = GenerateEncodingSymbols(heap->Heap[1]);
	DestroyHeapAndAllNodes(heap);
	fclose(file);
	free(frequencies);
	return table;
}

bool Can_serialize_table_test(){
	SETUP();
	TEST_FOR(AssertNotNull(array));
	TEARDOWN();
}

bool Serialized_table_length_is_correct(){
	SETUP();
	TEST_FOR(AssertEquals(array->Bits[0], 0x02));
	TEST_FOR(AssertEquals(array->Bits[1] & 0x80, 0x00));
	TEARDOWN();
}

bool Symbol_1_is_encoded_correctly(){
	SETUP();
	//'a' = 97 | b01100001
	//length = 1, symbol = b1 | 000011
	TEST_FOR(AssertEquals(array->Bits[1], 0x30));
	TEST_FOR(AssertEquals(array->Bits[2], 0x86));
	DISPLAY_BIT_ARRAY_DEF(array);
	DISPLAY_SYMBOL_TABLE_DEF(table);
	TEARDOWN();
}

bool Symbol_2_is_encoded_correctly(){
	SETUP();
	//TEST_FOR(AssertEquals(array->Bits[2] & 0x80, 0x00));
	TEARDOWN();
}
