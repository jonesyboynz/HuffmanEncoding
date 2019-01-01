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
		uint32_t totalTests = TotalTestsCount(siblingSet);
		if(failedTests > 0){
			ExecutionTestsFailed(totalTests,
				failedTests,
				((float) (totalTests - failedTests)) / ((float) totalTests) * 100.0);
			allTestsPassed = False;
		}
		else{
			ExecutionAllPassed();
		}
		siblingSet = siblingSet->Next;
	}
	return allTestsPassed;
}