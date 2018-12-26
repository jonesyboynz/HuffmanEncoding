#include <stdio.h>
#include <stdlib.h>
#include "Test.h"
#include "../../../Source/Encoding/CharacterFrequencies.h"

TestSet* Character_frequency_test_set(){
	TestSet* set = NewTestSet("Character frequency");
	AddTest(set, NewTest("Frequencies are correct", Character_frequency_test, False));
	return set;
}

bool Character_frequency_test(){
	FILE* file = fopen("Test/Data/frequency_test1", "rb");
	uint8_t* frequencies = CharacterFrequency(file);
	bool result = AssertEquals(frequencies['a'], 1)
		& AssertEquals(frequencies['e'], 1)
		& AssertEquals(frequencies['i'], 1)
		& AssertEquals(frequencies['o'], 1)
		& AssertEquals(frequencies['u'], 1);
	free(frequencies);
	fclose(file);
	return result;
}