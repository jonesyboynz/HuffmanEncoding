#include "Execution.h"
#include "Messages.h"
#include <stdlib.h>

bool Execute(TestSet* testSet){
	ExecutionStart();
	bool allTestsPassed = True;
	if (testSet == NULL){
		ExecutionNoTests();
	}
	TestSet* siblingSet = testSet;
	while(siblingSet != NULL){
		RunTestSet(siblingSet, 0);
		uint32_t failedTests = TotalTestsFailed(siblingSet);
		if(failedTests > 0){
			ExecutionTestsFailed(failedTests);
			allTestsPassed = False;
		}
		else{
			ExecutionAllPassed();
		}
		siblingSet = siblingSet->Next;
	}
	return allTestsPassed;
}