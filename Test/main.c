#include <stdio.h>
#include <stdlib.h>
#include "../Test/Framework/TestSet.h"


bool TestFunc(void){
	return True;
}

int main(int argc, char** argv){
	printf("TEST: Hello world!\n");
	TestSet* set = NewTestSet("TestSet");
	Test* test = NewTest("Test", TestFunc);
	AddTest(set, test);
	return 0;
}
