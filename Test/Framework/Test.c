#include "Test.h"
#include <stdlib.h>
#include <string.h>

Test* NewTest(char* name, bool (*function)(void)){
	Test* test = calloc(1, sizeof(Test));
	test->TestFunction = function;
	memcpy(test->Name, name, TEST_NAME_LENGTH);		//Copy name.
	test->Name[TEST_NAME_LENGTH - 1] = 0;			//Ensure final character is null terminator.
	return test;
}

void DestroyTest(Test* test){
	if (test->Next != NULL){
		DestroyTest(test->Next);
	}
	free(test);
	return;
}

bool RunTest(Test* test){
	test->Passed = test->TestFunction();
	test->Run = True;
	return test->Passed;
}