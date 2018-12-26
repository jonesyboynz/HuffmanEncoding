#include "Messages.h"
#include <stdio.h>

void TestMessagePassed(){
	printf("[PASSED]\n");
}

void TestMessageFailed(){
	printf("[FAILED]\n");
}

void TestMessageRunning(char* name, uint8_t depth){
	DisplayDepth(depth);
	printf("%s: ", name);
}

void TestSetMessageRunning(char* name, uint8_t depth){
	DisplayDepth(depth);
	printf("Running set: %s\n", name);
}

void TestSetMessageSummary(uint32_t passed, uint32_t failed, uint8_t depth){
	DisplayDepth(depth);
	printf("Set complete: Passed %d, ", passed);
	printf("Failed %d\n", failed);
}

void ExecutionStart(){
	printf("\nBeginning Test Execution\n\n");
}

void ExecutionNoTests(){
	printf("No tests to be executed.\n");
}

void ExecutionAllPassed(){
	printf("\nAll tests passed.\n");
}

void ExecutionTestsFailed(uint32_t failed){
	printf("\nError! %d test(s) failed.\n", failed);	
}

void DisplayDepth(uint8_t depth){
	for (uint8_t i = 0; i < depth; i++){
		printf("\t");
	}
}