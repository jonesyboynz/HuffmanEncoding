/*
Creates a boolean data type and defines True & False 
*/

#ifndef BOOL_H
#define BOOL_H

#include <stdint.h>

typedef uint8_t bool;

#define True ((bool) 1)
#define False ((bool) 0)

#endif