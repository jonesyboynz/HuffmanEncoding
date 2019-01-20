#include "Decode.h"
#include "Deserializer.h"

void Decode(FILE* inputFile, FileOutputStream* outputStream){

	FileInputStream* inputStream = NewFileInputStream(inputFile);

	SymbolTable* table = DeserializeSymbolTable(inputStream);

	/*

	Decode process:
		- decode symbol table
		- decode bytes

	Symbol table:
		- shift N bytes into var for table length
		- for each symbol - 1
			- shift Y bytes for symbol character
			- shift X bytes for symbol length
			- shift X' bytes into bit array for symbol bits.
		- shift X bytes for eof length
		- shift X' bytes into bit array for eof bits.

	*/


	//Cleanup
	DestoryFileInputStream(inputStream);
	DestroySymbolTable(table);
}