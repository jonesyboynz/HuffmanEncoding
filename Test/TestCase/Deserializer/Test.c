#include "Test.h"
#include "../../Framework/Framework.h"
#include "../../../Source/Decoding/Deserializer.h"

#define SETUP() SETUP_BASE(); FileInputStream* inputStream = NewFileInputStream(fopen("Test/Data/deserializer_test_data", "rb")); SymbolTable* table = DeserializeSymbolTable(inputStream)
#define TEARDOWN() DestoryFileInputStream(inputStream); DestroySymbolTable(table); TEARDOWN_BASE()

bool Deserializer_test_case_1(void);

TestSet* Deserializer_test_set(){
	TestSet* set = NewTestSet("Deserializer test set");
	AddTest(set, NewTest("Deserializer test case 1", Deserializer_test_case_1, False));
	return set;
}

//==========================================================================
//							TEST CASES
//==========================================================================

bool Deserializer_test_case_1(void){
	SETUP();
	
	DISPLAY_SYMBOL_TABLE_DEF(table);

	TEARDOWN();
}


