/*
Methods for asserting functionality.
*/

#ifndef ASSERT_H
#define ASSERT_H

#include "CoreIncludes.h"

bool AssertBytesMatch(void* test, void* against, uint32_t count);

bool AssertEquals(uint32_t test, uint32_t against);

bool AssertTrue(bool value);

bool AssertFalse(bool value);

void DisplayBytes(uint8_t* bytes, uint32_t count);

#endif