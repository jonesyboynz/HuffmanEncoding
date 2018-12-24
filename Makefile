LIBS = -lpthread -lm

CC = gcc -Iinclude -I./src -lm

CFLAGS = -g -Wall --std=gnu99

.PHONY: default all clean

default: clean huff

all: clean huff test

HUFF_DEPS = Source/Framework/Bool.h Source/Framework/CoreIncludes.h

TEST_DEPS = Test/Framework/CoreIncludes.h Test/Framework/Test.h Test/Framework/TestSet.h

DEPS = $(HUFF_DEPS) $(TEST_DEPS)

TEST_OBJ = $(HUFF_OBJ) Test/Framework/Test.o Test/Framework/TestSet.o

HUFF_OBJ = 

HUFF_BUILD = Source/main.o $(HUFF_OBJ)

TEST_BUILD = Test/main.o $(TEST_OBJ)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
test: $(TEST_BUILD)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

huff: $(HUFF_BUILD)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	-rm -f Source/*.o Test/*.o
	-rm test
	-rm huff
