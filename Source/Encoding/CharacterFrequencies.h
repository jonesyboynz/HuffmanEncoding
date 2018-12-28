/*
Function for calculating the frequencies of each character in a file.
*/

#ifndef CHARACTER_FREQUENCIES_H
#define CHARACTER_FREQUENCIES_H

#include <stdio.h>
#include <stdint.h>
#include "../Framework/Framework.h"

uint32_t* CharacterFrequency(FILE* openFile);

HuffHeap* GetHeapFromFrequencies(uint32_t* frequencies);

#endif