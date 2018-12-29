/*
Function for calculating the frequencies of each character in a file.
*/

#ifndef CHARACTER_FREQUENCIES_H
#define CHARACTER_FREQUENCIES_H

#include "../Framework/Framework.h"

Frequency* CharacterFrequency(FILE* openFile);

HuffHeap* GetHeapFromFrequencies(Frequency* frequencies);

#endif