/*
Defines a test and methods to create, execute and destroy it.
*/

#ifndef TEST_H
#define TEST_H

#include "../../Test/Framework/CoreIncludes.h"

typedef struct test_s Test;

struct test_s {
	char Name[TEST_NAME_LENGTH];
	bool (*TestFunction)(void);
	bool Run;
	bool NoAssert; //Test does not assert on error (no fancy message).
	bool Passed;
	Test* Next;
};

Test* NewTest(char* name, bool (*Function)(void), bool noAssert);

void DestroyTest(Test* test);

bool RunTest(Test* test, uint8_t depth);

#endif