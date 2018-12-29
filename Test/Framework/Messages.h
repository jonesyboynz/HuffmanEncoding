/*
Messages to be displayed when running tests.
*/

#ifndef MESSAGES_H
#define MESSAGES_H

#include "../../Test/Framework/CoreIncludes.h"

//Tests

void TestMessagePassed();

void TestMessageFailed();

void TestMessageRunning(char* name, uint8_t depth);

//Test Sets

void TestSetMessageRunning(char* name, uint8_t depth);

void TestSetMessageSummary(uint32_t passed, uint32_t failed, uint8_t depth);

//Execution

void ExecutionStart();

void ExecutionNoTests();

void ExecutionAllPassed();

void ExecutionTestsFailed(uint32_t failed, float percentage);

//Other

void DisplayDepth(uint8_t depth);

#endif