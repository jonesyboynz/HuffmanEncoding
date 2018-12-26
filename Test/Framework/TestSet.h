/*
Defines a set of tests.
Can have child test sets which will be run prior to any tests.
*/

#ifndef TEST_SET_H
#define TEST_SET_H

#include "Test.h"
#include "../../Test/Framework/CoreIncludes.h"

typedef struct test_set_s TestSet;

struct test_set_s {
	char Name[TEST_NAME_LENGTH];

	TestSet* Next;			//Linked-list of sibling test sets.
	TestSet* ChildSetRoot; 	//Child test sets.
	Test* TestRoot;			//Tests.		

	bool Run;

	//Just for this node.
	uint32_t TestCount; 
	uint32_t Passed;
	uint32_t Failed;
};

void DestroyTestSet(TestSet* testSet);

TestSet* NewTestSet(const char* name);

bool RunTestSet(TestSet* testSet, uint8_t depth); //Note: does not run sibling tests.

void AddTest(TestSet* testSet, Test* test);

void AddChildTestSet(TestSet* testSet, TestSet* childTestSet);

uint32_t TotalTestsFailed(TestSet* testSet);

uint32_t TotalTestsCount(TestSet* testSet);

#endif