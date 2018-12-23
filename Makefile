LIBS = -lpthread -lm
CC = gcc -Iinclude -I./src -lm
CFLAGS = -g -Wall --std=gnu99

.PHONY: default all clean

DEPS = 

OBJECTS = 

HUFF_OBJ = Source/main.o $(OBJECTS)

HUFF_TEST_OBJ = Test/main.o $(OBJECTS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
test: $(HUFF_TEST_OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

huff: $(HUFF_OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	-rm -f Source/*.o Test/*.o
	-rm test
	-rm huff

default: clean huff

all: clean huff test
