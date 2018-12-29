#include <stdio.h>
#include <stdlib.h>
#include "Test.h"
#include "../../../Source/Encoding/CharacterFrequencies.h"

bool Character_frequency_test1();

bool Character_frequency_test2();

bool Frequency_to_heap_test();

TestSet* Character_frequency_test_set(){
	TestSet* set = NewTestSet("Character frequency");
	AddTest(set, NewTest("Frequencies are correct", Character_frequency_test1, False));
	AddTest(set, NewTest("Frequencies are correct", Character_frequency_test2, False));
	AddTest(set, NewTest("Can convert frequencies to heap", Frequency_to_heap_test, False));
	return set;
}

bool Character_frequency_test1(){
	FILE* file = fopen("Test/Data/frequency_test1", "rb");
	Frequency* frequencies = CharacterFrequency(file);
	bool result = AssertEquals(frequencies['a'], 1)
		& AssertEquals(frequencies['e'], 1)
		& AssertEquals(frequencies['i'], 1)
		& AssertEquals(frequencies['o'], 1)
		& AssertEquals(frequencies['u'], 1);
	free(frequencies);
	fclose(file);
	return result;
}

bool Character_frequency_test2(){
	FILE* file = fopen("Test/Data/frequency_test2", "rb");
	Frequency* frequencies = CharacterFrequency(file);
	bool result = AssertEquals(frequencies['d'], 2)
		& AssertEquals(frequencies['T'], 1)
		& AssertEquals(frequencies['Z'], 0)
		& AssertEquals(frequencies['z'], 1)
		& AssertEquals(frequencies['.'], 1)
		& AssertEquals(frequencies['o'], 4);
	free(frequencies);
	fclose(file);
	return result;
}

bool Frequency_to_heap_test(){
	FILE* file = fopen("Test/Data/frequency_test2", "rb");
	Frequency* frequencies = CharacterFrequency(file);
	HuffHeap* heap = GetHeapFromFrequencies(frequencies);
	bool result = AssertEquals(heap->Heap[1]->Character, '.'); //The lowest character codes will be placed on the heap first.
	result &= AssertEquals(heap->Count, 28);
	result &= AssertEquals(heap->Heap[16]->Character, ' ');
	DestroyHeapAndAllNodes(heap);
	return result;
}