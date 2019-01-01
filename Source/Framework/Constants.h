/*
System constants
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

//2^8 symbols since encoding is done for single bytes. 
#define SYSTEM_SYMBOL_COUNT 256

//Worst-case symbol length is 255 bits when encoding 8-bit values.
#define SYSTEM_SYMBOL_MAX_BITS 255

//255 bits occupies 32 bytes (with 1 bit unused).
#define SYSTEM_SYMBOL_MAX_BYTES 32

//Logical and with a byte to get the first bit.
#define BIT_MASK 0x01

//Should be self explanitory
#define BITS_IN_BYTE 8

//Bits
#define BIT0 0x00
#define BIT1 0x01
#define BIT_ERROR 0xFF

//Bytes
#define BYTE_ERROR 0xFF

//Exit statuses.
#define EXIT_SUCCESS 0
#define EXIT_FAIL 2

#endif
