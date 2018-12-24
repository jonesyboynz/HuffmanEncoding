/*
Defines a set of tests.
*/

#ifndef TEST_SET_H
#define TEST_SET_H

#include "Test.h"
#include "../../Test/Framework/CoreIncludes.h"

typedef struct test_set_s TestSet;

struct test_set_s {
	char* Name[TEST_NAME_LENGTH];

	TestSet* Next;			//Linked-list of sibling test sets.
	TestSet* ChildSetRoot; 	//Child test sets.
	Test* TestRoot;			//Tests.		

	bool Run;
	bool SkipOnFailure; //Skip once a test fails.

	//Just for this node.
	uint32_t TestCount; 
	uint32_t Passed;
	uint32_t Failed;
	uint32_t Skipped;

	//These counts include children.
	uint32_t TotalTestCount; 
	uint32_t TotalPassed;
	uint32_t TotalFailed;
	uint32_t TotalSkipped;
};

void DestroyTestSet(TestSet* testSet);

TestSet* NewTestSet(const char* name);

bool Run(TestSet* testSet);

void AddTest(TestSet* testSet, Test* test);

void AddChildTestSet(TestSet* testSet, TestSet* childTestSet);

#endif