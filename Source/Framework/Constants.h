/*
System constants
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

//2^8 symbols since encoding is done for single bytes. 
#define SYSTEM_SYMBOL_COUNT 257 //1 extra for EOF symbol.

//Worst-case symbol length is 255 bits when encoding 8-bit values.
//But now we need 9 bits because there is 1 extra symbol for the EOF.
#define SYSTEM_SYMBOL_MAX_BITS 256

//256 bits occupies 32 bytes.
#define SYSTEM_SYMBOL_MAX_BYTES 32

//Symbols that use 256 bits require 9 bits to encode their length.
#define SYMBOL_LENGTH_BITS 9

//Logical and with a byte to get the first bit.
#define BIT_MASK 0x01

//Should be self explanitory
#define BITS_IN_BYTE 8

//Bits
#define BIT0 0x00
#define BIT1 0x01
#define BIT_ERROR 0xFF

//Bytes
#define BYTE_ERROR 0xFF //Note: this is a valid byte...

//Exit statuses.
#define EXIT_SUCCESS 0
#define EXIT_FAIL 2

//Defines symbol types.
#define SYMBOL_TYPE_PARENT		0x01
#define SYMBOL_TYPE_CHARACTER 	0x02
#define SYMBOL_TYOE_EOF 		0x04

#define BYTE_UNUSED 0x00

//EOF symbol character position
#define EOF_CHARACTER_VALUE 256

#endif
