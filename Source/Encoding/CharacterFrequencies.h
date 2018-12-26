/*
Function for calculating the frequencies of each character in a file.
*/

#ifndef CHARACTER_FREQUENCIES_H
#define CHARACTER_FREQUENCIES_H

#include <stdio.h>
#include <stdint.h>

#define CHARACTER_SET_LENGTH 256

uint8_t* CharacterFrequency(FILE* openFile);

#endif