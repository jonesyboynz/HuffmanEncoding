#Compiler macros
LIBS = -lpthread -lm
CC = gcc -Iinclude -I./src -lm
CFLAGS = -g -Wall --std=gnu99

.PHONY: default all clean

default: all

all: clean huff test

clean: clean_test clean_huff

HUFF_FRAMEWORK_DEPS = Source/Framework/Bool.h Source/Framework/Constants.h Source/Framework/Messages.h Source/Framework/CoreIncludes.h Source/Framework/HuffTreeNode.h Source/Framework/HuffTree.h Source/Framework/HuffNodeHeap.h Source/Framework/Framework.h
HUFF_FRAMEWORK_OBJ = Source/Framework/Messages.o Source/Framework/HuffTreeNode.o Source/Framework/HuffTree.o Source/Framework/HuffNodeHeap.o

HUFF_ENCODING_DEPS = Source/Encoding/CharacterFrequencies.h
HUFF_ENCODING_OBJ = Source/Encoding/CharacterFrequencies.o

HUFF_DECODING_DEPS = 
HUFF_DECODING_OBJ = 

HUFF_DEPS = $(HUFF_FRAMEWORK_DEPS) $(HUFF_ENCODING_DEPS) $(HUFF_DECODING_DEPS)
HUFF_OBJ = $(HUFF_FRAMEWORK_OBJ) $(HUFF_ENCODING_OBJ) $(HUFF_DECODING_OBJ)

TEST_FRAMEWORK_DEPS = Test/Framework/CoreIncludes.h Test/Framework/Test.h Test/Framework/TestSet.h Test/Framework/Messages.h Test/Framework/Assert.h Test/Framework/Execution.h Test/Framework/Framework.h
TEST_FRAMEWORK_OBJ = Test/Framework/Messages.o Test/Framework/Test.o Test/Framework/TestSet.o Test/Framework/Assert.o Test/Framework/Execution.o

TEST_CASE_DEPS = Test/TestCase/CharacterFrequency/Test.h Test/TestCase/HuffTree/Test.h Test/TestCase/HuffHeap/Test.h
TEST_CASE_OBJ = Test/TestCase/CharacterFrequency/Test.o Test/TestCase/HuffTree/Test.o Test/TestCase/HuffHeap/Test.o

TEST_DEPS = $(TEST_FRAMEWORK_DEPS) $(TEST_CASE_DEPS) Test/AllTestCases.h
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
	-rm -f -R *.o
	-rm test

clean_huff:
	-rm -f -R *.o
	-rm huff
