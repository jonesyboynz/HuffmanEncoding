#include "TestSet.h"
#include <string.h>
#include <stdlib.h>

TestSet* NewTestSet(const char* name){
	TestSet* testSet = calloc(1, sizeof(TestSet));
	memcpy(testSet->Name, name, TEST_NAME_LENGTH); 	//Copy name.
	testSet->Name[TEST_NAME_LENGTH - 1] = 0;		//Ensure final character is null terminator.
	return testSet;
}

void DestroyTestSet(TestSet* testSet){
	DestroyTestSet(testSet->Next);
	DestroyTestSet(testSet->ChildSetRoot);
	DestroyTest(testSet->TestRoot);
	free(testSet);
	return;
}

bool Run(TestSet* testSet){
	/*
	uint32_t skippedTests;
	uint32_t passedTests;
	uint32_t failedTests;

	TestSet* childSet = testSet->ChildSetRoot;
	while(childSet != NULL){

		childSet = childSet->Next;
	}


	Test* test = testSet->TestRoot;
	while(test != NULL){
		if (Run(test) == False && testSet->SkipOnFailure == True){

		}
		test = test->Next;
	}
	*/



	return False;
}


void AddTest(TestSet* testSet, Test* test){
	if (testSet->TestRoot == NULL){ //Initial Case.
		testSet->TestRoot = test;
	}
	else{
		TestSet* currentTest= testSet->TestRoot;
		while(currentTest->Next != NULL){ //Find the child test at the end of the linked list.
			currentTest = currentTest->Next;
		}
		currentTest->Next = test; //Append the test to the end of the test linked list.
	}
	testSet->TestCount += 1;
	testSet->TotalTestCount += 1;
	return;
}

void AddChildTestSet(TestSet* testSet, TestSet* childTestSet){
	if (testSet->ChildSetRoot == NULL){ //Initial Case.
		testSet->ChildSetRoot = childTestSet;
	}
	else{
		TestSet* currentTestSet = testSet->ChildSetRoot;
		while(currentTestSet->Next != NULL){ //Find the child test set at the end of the linked list.
			currentTestSet = currentTestSet->Next;
		}
		currentTestSet->Next = childTestSet; //Append the test set to the end of the child test set.
	}
	testSet->TotalTestCount += childTestSet->TotalTestCount;
	return;
}
