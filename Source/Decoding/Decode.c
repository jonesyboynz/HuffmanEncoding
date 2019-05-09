#include "Decode.h"
#include "Deserializer.h"

bool DecodeFie();

void Decode(FILE* inputFile, FileOutputStream* outputStream){

	//Create an input stream.
	FileInputStream* inputStream = NewFileInputStream(inputFile);

	//Deserialize the symbol table.
	SymbolTable* table = DeserializeSymbolTable(inputStream);
	DISPLAY_SYMBOL_TABLE_DEF(table);

	//Convert the symbol table to a decoding state machine.
	HuffNode* tree = GenerateTreeFromTable(table);

	if (ValidateTree(tree) == False){
		DecodingError("Invalid decoding state machine. Symbol table has been corrupted or file is not huffman encoded.");
		return;
	}

	//Decode the file.
	DecodeFie(inputStream, outputStream, tree);

	//Ensure the output buffer is written.
	FinishOutput(outputStream);

	//Cleanup
	DestoryFileInputStream(inputStream);
	DestroySymbolTable(table);
}

/*
============================================================================
						PRIVATE METHODS
============================================================================
*/

bool DecodeFie(FileInputStream* inputStream, FileOutputStream* outputStream, HuffNode* root){
	bool eof_reached = False;
	HuffNode* current_node = root;

	while (inputStream->EndOfFile == False){
		for (size_t index = inputStream->CurrentBit; index < inputStream->Buffer->Count; index++){

			if (GetBit(inputStream->Buffer, index) == BIT0){
				DISPLAY_MESSAGE("0", DISPLAY_OPTION_NO_NEWLINE);
				current_node = current_node->Left;
			}
			else{
				DISPLAY_MESSAGE("1", DISPLAY_OPTION_NO_NEWLINE);
				current_node = current_node->Right;
			}

			if (current_node->Type == SYMBOL_TYPE_CHARACTER){
				printf(" c:\"%c\"\n", current_node->Character);
				PushByteToStream(outputStream, current_node->Character);
				current_node = root;
			}
			else if (current_node->Type == SYMBOL_TYOE_EOF){
				DISPLAY_MESSAGE_DEF("\nEOF");
				eof_reached = True;
				break;
			}
		}
		DISPLAY_MESSAGE_DEF("Next bytes");
		GetNextBytes(inputStream);
	}

	if (eof_reached == True && inputStream->EndOfFile == False){
		DecodingError("End of file symbol detected before end of file was reached. Some data has not been decoded. File may have been corrupted.");
		return False;
	}
	if (eof_reached == False && inputStream->EndOfFile == True){
		DecodingError("End of file reached, but no end of file symbol was present. File may have been corrupted.");
		return False;
	}
	return True;
}