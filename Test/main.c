#include <stdio.h>
#include <stdlib.h>
#include "Framework/Framework.h"


bool CanRunFunction(void){
	return True;
}

int main(int argc, char** argv){
	
	//Core test set.
	TestSet* coreTestSet = NewTestSet("Tests");

	//Basic tests.
	TestSet* basicTestSet = NewTestSet("Basic tests");
	Test* basicTest = NewTest("Tests can run", CanRunFunction);
	AddTest(basicTestSet, basicTest);
	AddChildTestSet(coreTestSet, basicTestSet);

	//Run the tests.
	if (Execute(coreTestSet) == False){
		return 2;
	}
	return 0;
}
