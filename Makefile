#Compiler macros
LIBS = -lpthread -lm
CC = gcc -Iinclude -I./src -lm
CFLAGS = -g -Wall --std=gnu99

.PHONY: default all clean

default: all

all: clean huff test

clean: clean_test clean_huff

HUFF_FRAMEWORK_CORE_DEPS = Source/Framework/CoreTypes/Bool.h Source/Framework/CoreTypes/Bit.h Source/Framework/CoreTypes/Mode.h Source/Framework/CoreTypes/Frequency.h Source/Framework/Constants.h Source/Framework/CoreIncludes.h

HUFF_FRAMEWORK_DEPS = Source/Framework/BitArray.h Source/Framework/Messages.h Source/Framework/HuffTreeNode.h Source/Framework/HuffTree.h Source/Framework/HuffNodeHeap.h Source/Framework/Symbol.h Source/Framework/SymbolTable.h Source/Framework/FileOutputStream.h Source/Framework/ByteArray.h Source/Framework/Debug.h Source/Framework/Framework.h
HUFF_FRAMEWORK_OBJ =  Source/Framework/BitArray.o Source/Framework/Messages.o Source/Framework/HuffTreeNode.o Source/Framework/HuffTree.o Source/Framework/HuffNodeHeap.o Source/Framework/Symbol.o Source/Framework/SymbolTable.o Source/Framework/FileOutputStream.o Source/Framework/ByteArray.o Source/Framework/Debug.o

HUFF_ENCODING_DEPS = Source/Encoding/CharacterFrequencies.h Source/Encoding/Serializer.h Source/Encoding/Encode.h
HUFF_ENCODING_OBJ = Source/Encoding/CharacterFrequencies.o Source/Encoding/Serializer.o Source/Encoding/Encode.o

HUFF_DECODING_DEPS = Source/Decoding/Deserializer.h Source/Decoding/Decode.h
HUFF_DECODING_OBJ = Source/Decoding/Deserializer.o Source/Decoding/Decode.o

HUFF_DEPS = $(HUFF_FRAMEWORK_CORE_DEPS) $(HUFF_FRAMEWORK_DEPS) $(HUFF_ENCODING_DEPS) $(HUFF_DECODING_DEPS)
HUFF_OBJ = $(HUFF_FRAMEWORK_OBJ) $(HUFF_ENCODING_OBJ) $(HUFF_DECODING_OBJ)

TEST_FRAMEWORK_CORE_DEPS = Test/Framework/CoreIncludes.h

TEST_FRAMEWORK_DEPS = Test/Framework/Messages.h Test/Framework/Test.h Test/Framework/TestSet.h Test/Framework/Assert.h Test/Framework/Execution.h Test/Framework/SetupTeardown.h Test/Framework/Framework.h
TEST_FRAMEWORK_OBJ =  Test/Framework/Messages.o Test/Framework/Test.o Test/Framework/TestSet.o Test/Framework/Assert.o Test/Framework/Execution.o

TEST_CASE_DEPS = Test/TestCase/CharacterFrequency/Test.h Test/TestCase/HuffTree/Test.h Test/TestCase/HuffHeap/Test.h Test/TestCase/BitArray/Test.h Test/TestCase/Symbol/Test.h Test/TestCase/ByteArray/Test.h Test/TestCase/Serializer/Test.h
TEST_CASE_OBJ =  Test/TestCase/CharacterFrequency/Test.o Test/TestCase/HuffTree/Test.o Test/TestCase/HuffHeap/Test.o Test/TestCase/BitArray/Test.o Test/TestCase/Symbol/Test.o Test/TestCase/ByteArray/Test.o Test/TestCase/Serializer/Test.o

TEST_DEPS = $(TEST_FRAMEWORK_CORE_DEPS) $(TEST_FRAMEWORK_DEPS) $(TEST_CASE_DEPS) Test/TestCase/All.h
TEST_OBJ = $(HUFF_OBJ) $(TEST_FRAMEWORK_OBJ) $(TEST_CASE_OBJ)

DEPS = $(HUFF_DEPS) $(TEST_DEPS)

HUFF_BUILD = Source/main.o $(HUFF_OBJ)

TEST_BUILD = Test/main.o $(TEST_OBJ)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
test: $(TEST_BUILD)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

huff: $(HUFF_BUILD)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean_test:
	-find . -name '*.o' -delete
	-rm test

clean_huff:
	-find . -name '*.o' -delete
	-rm huff
