#include "TestSet.h"
#include "Messages.h"
#include <string.h>
#include <stdlib.h>

TestSet* NewTestSet(const char* name){
	TestSet* testSet = calloc(1, sizeof(TestSet));
	memcpy(testSet->Name, name, TEST_NAME_LENGTH); 	//Copy name.
	testSet->Name[TEST_NAME_LENGTH - 1] = 0;		//Ensure final character is null terminator.
	return testSet;
}

void DestroyTestSet(TestSet* testSet){
	if (testSet->Next != NULL){
		DestroyTestSet(testSet->Next);
	}
	if (testSet->ChildSetRoot != NULL){
		DestroyTestSet(testSet->ChildSetRoot);
	}
	if (testSet->TestRoot != NULL){
		DestroyTest(testSet->TestRoot);
	}
	free(testSet);
}

bool RunTestSet(TestSet* testSet, uint8_t depth){
	TestSetMessageRunning(testSet->Name, depth);
	
	/*
	Run the child test sets.
	*/
	bool allChildTestsPassed = True;
	TestSet* childSet = testSet->ChildSetRoot;
	while(childSet != NULL){
		if (RunTestSet(childSet, depth + 1) == False){
			allChildTestsPassed = False;
		}
		childSet = childSet->Next;
	}
	
	/*
	Run the tests held by this test set.
	*/
	Test* test = testSet->TestRoot;
	while(test != NULL){
		RunTest(test, depth + 1);
		if (test->Passed == True){
			testSet->Passed += 1;
		}
		else{
			testSet->Failed += 1;
		}
		test = test->Next;
	}

	//Mark test as run.
	testSet->Run = True;

	//Display summary message.
	uint8_t totalTests = TotalTestsCount(testSet);
	uint8_t totalFailed = TotalTestsFailed(testSet);
	TestSetMessageSummary(totalTests - totalFailed,
		totalFailed,
		depth);
	
	//Return the overall result of this test set's tests.
	if (testSet->Passed == testSet->TestCount && allChildTestsPassed == True){
		return True;
	}
	return False;
}


void AddTest(TestSet* testSet, Test* test){
	if (testSet->TestRoot == NULL){ //Initial Case.
		testSet->TestRoot = test;
	}
	else{
		Test* currentTest = testSet->TestRoot;
		while(currentTest->Next != NULL){ //Find the child test at the end of the linked list.
			currentTest = currentTest->Next;
		}
		currentTest->Next = test; //Append the test to the end of the test linked list.
	}
	testSet->TestCount += 1;
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
}

uint32_t TotalTestsFailed(TestSet* testSet){
	uint8_t failureCount = testSet->Failed;
	TestSet* childSet = testSet->ChildSetRoot;
	while(childSet != NULL){
		failureCount += TotalTestsFailed(childSet);
		childSet = childSet->Next;
	}
	return failureCount;
}

uint32_t TotalTestsCount(TestSet* testSet){
	uint8_t testCount = testSet->TestCount;
	TestSet* childSet = testSet->ChildSetRoot;
	while(childSet != NULL){
		testCount += TotalTestsCount(childSet);
		childSet = childSet->Next;
	}
	return testCount;	
}
