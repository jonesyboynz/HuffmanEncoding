#include "Messages.h"
#include <stdio.h>

void TestMessagePassed(){
	printf("[PASSED]\n");
	fflush(NULL);
}

void TestMessageFailed(){
	printf("[FAILED]\n");
	fflush(NULL);
}

void TestMessageRunning(char* name, uint8_t depth){
	DisplayDepth(depth);
	printf("%s: ", name);
	fflush(NULL);
}

void TestSetMessageRunning(char* name, uint8_t depth){
	DisplayDepth(depth);
	printf("Running set: %s\n", name);
	fflush(NULL);
}

void TestSetMessageSummary(uint32_t passed, uint32_t failed, uint8_t depth){
	DisplayDepth(depth);
	printf("Set complete: Passed %d, ", passed);
	printf("Failed %d\n", failed);
	fflush(NULL);
}

void ExecutionStart(){
	printf("\nBeginning Test Execution\n\n");
	fflush(NULL);
}

void ExecutionNoTests(){
	printf("No tests to be executed.\n");
	fflush(NULL);
}

void ExecutionAllPassed(){
	printf("\nAll tests passed (100%%).\n");
	fflush(NULL);
}

void ExecutionTestsFailed(uint32_t failed, float percentage){
	printf("\nError! %d test(s) failed (%f%%).\n", failed, percentage);
	fflush(NULL);	
}

void DisplayDepth(uint8_t depth){
	for (uint8_t i = 0; i < depth; i++){
		printf("\t");
	}
}