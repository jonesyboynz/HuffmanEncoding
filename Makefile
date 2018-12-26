LIBS = -lpthread -lm

CC = gcc -Iinclude -I./src -lm

CFLAGS = -g -Wall --std=gnu99

.PHONY: default all clean

default: all

all: clean huff test

clean: clean_test clean_huff

HUFF_DEPS = Source/Framework/Bool.h Source/Framework/CoreIncludes.h

TEST_DEPS = Test/Framework/CoreIncludes.h Test/Framework/Test.h Test/Framework/TestSet.h Test/Framework/Messages.h Test/Framework/Execution.h Test/Framework/Framework.h

DEPS = $(HUFF_DEPS) $(TEST_DEPS)

TEST_OBJ = $(HUFF_OBJ) Test/Framework/Messages.o Test/Framework/Test.o Test/Framework/TestSet.o Test/Framework/Execution.o

HUFF_OBJ = 

HUFF_BUILD = Source/main.o $(HUFF_OBJ)

TEST_BUILD = Test/main.o $(TEST_OBJ)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
test: $(TEST_BUILD)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

huff: $(HUFF_BUILD)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean_test:
	-rm -f Test/*.o
	-rm test

clean_huff:
	-rm -f Source/*.o
	-rm huff
