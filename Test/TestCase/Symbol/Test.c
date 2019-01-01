#include "Test.h"
#include "../../Framework/Framework.h"
#include "../../../Source/Encoding/CharacterFrequencies.h"

bool Can_create_symbol_table();

bool Symbol_table_is_correct();

TestSet* Symbol_test_set(){
	TestSet* set = NewTestSet("Symbol tests");
	AddTest(set, NewTest("Can create symbol table", Can_create_symbol_table, True));
	AddTest(set, NewTest("Symbol table is correct", Symbol_table_is_correct, True));
	return set;
}

bool Can_create_symbol_table(){
	SymbolTable* table = NewSymbolTable();
	bool result = AssertNotNull(table);
	DestroySymbolTable(table);
	return result;
}

bool Symbol_table_is_correct(){
	FILE* file = fopen("Test/Data/symbol_table_test_data", "rb");
	Frequency* frequencies = CharacterFrequency(file);
	HuffHeap* heap = GetHeapFromFrequencies(frequencies);
	GenerateTreeWithinHeap(heap);
	SymbolTable* table = GenerateEncodingSymbols(heap->Heap[1]);
	bool result = AssertEquals(table->Table['1']->BitArray->Bits[0], 0xC0);
	result &= AssertEquals(table->Table['2']->BitArray->Bits[0], 0xC8);
	result &= AssertEquals(table->Table['3']->BitArray->Bits[0], 0xD8);
	result &= AssertEquals(table->Table['4']->BitArray->Bits[0], 0xD0);
	result &= AssertEquals(table->Table[':']->BitArray->Bits[0], 0xE0);
	result &= AssertEquals(table->Table['a']->BitArray->Bits[0], 0x00);
	result &= AssertEquals(table->Table['c']->BitArray->Bits[0], 0xF0);
	result &= AssertEquals(table->Table['z']->BitArray->Bits[0], 0x80);
	DestroyHeapAndAllNodes(heap);
	DestroySymbolTable(table);
	return result;	
}


