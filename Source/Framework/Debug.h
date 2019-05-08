/*
Provides methods for debugging data structures.
*/

#ifndef DEBUG_H
#define DEBUG_H

#include "CoreIncludes.h"
#include "BitArray.h"
#include "Symbol.h"
#include "SymbolTable.h"
#include "HuffTreeNode.h"
#include "HuffNodeHeap.h"

typedef uint16_t DebugDisplayOptions;

#define DISPLAY_OPTION_DEFAULT 		0x0000
#define DISPLAY_OPTION_NO_NEWLINE 	0x0001 //No newline
#define DISPLAY_OPTION_EXPLICIT 	0x0002 //Display everything
#define DISPLAY_OPTION_NO_FLUSH 	0x0004 //Display everything

void DisplayMessage(const char* message, DebugDisplayOptions option); 

void DisplayBinary(uint8_t byte, DebugDisplayOptions option);

void DisplayHuffHeap(HuffHeap* heap, DebugDisplayOptions options);

void DisplayFrequencyTable(Frequency* frequencies, DebugDisplayOptions option);

void DisplayHuffTree(HuffNode* root, DebugDisplayOptions option);

void DisplayBitArray(BitArray* array, DebugDisplayOptions option);

void DisplayHuffNode(HuffNode* node, DebugDisplayOptions option);

void DisplaySymbolTable(SymbolTable* table, DebugDisplayOptions option);

void DisplaySymbol(Symbol* symbol, DebugDisplayOptions option);

//Overloads. These will use DISPLAY_OPTION_DEFAULT in all cases.

#define DISPLAY_BINARY(byte, option) DisplayBinary(byte, option)
#define DISPLAY_BINARY_DEF(byte) DISPLAY_BINARY(byte, DISPLAY_OPTION_DEFAULT)

#define DISPLAY_HUFF_HEAP(heap, option) DisplayHuffHeap(heap, option)
#define DISPLAY_HUFF_HEAP_DEF(heap) DISPLAY_HUFF_HEAP(heap, DISPLAY_OPTION_DEFAULT)

#define DISPLAY_FREQUENCY_TABLE(frequencies, option) DisplayFrequencyTable(frequencies, option)
#define DISPLAY_FREQUENCY_TABLE_DEF(frequencies) DISPLAY_FREQUENCY_TABLE(frequencies, DISPLAY_OPTION_DEFAULT)

#define DISPLAY_HUFF_TREE(root, option) DisplayHuffTree(root, option)
#define DISPLAY_HUFF_TREE_DEF(root) DISPLAY_HUFF_TREE(root, DISPLAY_OPTION_DEFAULT)

#define DISPLAY_BIT_ARRAY(array, option) DisplayBitArray(array, option)
#define DISPLAY_BIT_ARRAY_DEF(array) DISPLAY_BIT_ARRAY(array, DISPLAY_OPTION_DEFAULT)

#define DISPLAY_HUFF_NODE(node, option) DisplayHuffNode(node, option)
#define DISPLAY_HUFF_NODE_DEF(node) DISPLAY_HUFF_NODE(node, DISPLAY_OPTION_DEFAULT)

#define DISPLAY_SYMBOL_TABLE(table, option) DisplaySymbolTable(table, option)
#define DISPLAY_SYMBOL_TABLE_DEF(table) DISPLAY_SYMBOL_TABLE(table, DISPLAY_OPTION_DEFAULT)

#define DISPLAY_SYMBOL(symbol, option) DisplaySymbol(symbol, option)
#define DISPLAY_SYMBOL_DEF(symbol) DISPLAY_SYMBOL(symbol, DISPLAY_OPTION_DEFAULT)

#define DISPLAY_MESSAGE(symbol, option) DisplayMessage(symbol, option)
#define DISPLAY_MESSAGE_DEF(symbol) DISPLAY_MESSAGE(symbol, DISPLAY_OPTION_DEFAULT)

#endif