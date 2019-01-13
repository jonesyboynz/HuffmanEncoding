/*
Type for the mode & settins which the system is running with.
*/

#ifndef MODE_H
#define MODE_H

typedef uint32_t Mode;

#define MODE_IS_SET(mode, x) (mode & x) > 0 

//Modes
#define MODE_ENCODE ((Mode) 0x01)
#define MODE_DECODE ((Mode) 0x02)
#define MODE_INVALID ((Mode) 0x04)

#endif