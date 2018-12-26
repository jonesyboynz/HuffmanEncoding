#include "Test.h"
#include "Messages.h"
#include <stdlib.h>
#include <string.h>

Test* NewTest(char* name, bool (*function)(void), bool noAssert){
	Test* test = calloc(1, sizeof(Test));
	test->TestFunction = function;
	memcpy(test->Name, name, TEST_NAME_LENGTH);		//Copy name.
	test->Name[TEST_NAME_LENGTH - 1] = 0;			//Ensure final character is null terminator.
	test->NoAssert = noAssert;
	return test;
}

void DestroyTest(Test* test){
	if (test->Next != NULL){
		DestroyTest(test->Next);
	}
	free(test);
}

bool RunTest(Test* test, uint8_t depth){
	TestMessageRunning(test->Name, depth);
	test->Passed = test->TestFunction();
	test->Run = True;
	if (test->Passed == True){
		TestMessagePassed();
	}
	else if (test->NoAssert == True){
		TestMessageFailed();
	}
	//Else the test should display a message on failure.
	return test->Passed;
}
