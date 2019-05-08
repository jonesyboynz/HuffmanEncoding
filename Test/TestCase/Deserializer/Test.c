#include "Test.h"
#include "../../Framework/Framework.h"
#include "../../../Source/Decoding/Deserializer.h"

#define SETUP() SETUP_BASE(); FileInputStream* inputStream = NewFileInputStream(fopen("Test/Data/deserializer_test_data", "rb")); SymbolTable* table = DeserializeSymbolTable(inputStream)
#define TEARDOWN() DestoryFileInputStream(inputStream); DestroySymbolTable(table); TEARDOWN_BASE()

bool Can_generate_symbol_table(void);

bool Can_generate_tree_from_symbol_table();

TestSet* Deserializer_test_set(){
	TestSet* set = NewTestSet("Deserializer test set");
	AddTest(set, NewTest("Can generate symbol table", Can_generate_symbol_table, False));
	AddTest(set, NewTest("Can generate tree from symbol table", Can_generate_tree_from_symbol_table, False));
	return set;
}

//==========================================================================
//							TEST CASES
//==========================================================================

bool Can_generate_symbol_table(void){
	SETUP();
	TEST_FOR(AssertEquals((uint32_t) table->Table['b']->Character, (uint32_t) 'b'));
	TEST_FOR(AssertEquals((uint32_t) table->Table['b']->BitArray->Bits[0], (uint32_t) 0x40));
	TEST_FOR(AssertEquals((uint32_t) table->Table[133]->BitArray->Bits[0], (uint32_t) 0x80));
	TEST_FOR(AssertEquals((uint32_t) table->Table[256]->BitArray->Bits[0], (uint32_t) 0x00));
	TEARDOWN();
}

bool Can_generate_tree_from_symbol_table(){
	SETUP();
	//DISPLAY_SYMBOL_TABLE_DEF(table);
	HuffNode* tree = GenerateTreeFromTable(table);
	//DISPLAY_HUFF_TREE_DEF(tree);
	TEST_FOR(AssertTrue(tree != NULL));
	TEARDOWN();	
}