/*
Handles messaging.
*/

#ifndef SOURCE_MESSAGES_H
#define SOURCE_MESSAGES_H

#include "CoreIncludes.h"

void UsageMessage();

void UnableToOpenInputMessage(char* filename);

void UnableToOpenOutputMessage(char* filename);

void ModeInvalidMessage(char* mode);

void DecodingError(char* message);

#endif