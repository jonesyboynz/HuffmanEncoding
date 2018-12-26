#include <stdio.h>
#include "Assert.h"

bool AssertBytesMatch(void* test, void* against, uint32_t count){
	uint8_t* test_array = (uint8_t*) test;
	uint8_t* against_array = (uint8_t*) against;
	for (uint32_t i = 0; i < count; i++){
		if (test_array[i] != against_array[i]){
			printf("[Failed] at character %d. Expected: ", i);
			DisplayBytes(against_array, count);
			printf("got: ");
			DisplayBytes(test_array, count);
			printf(".\n");
			return False;
		}
	}
	return True;
}

bool AssertEquals(uint32_t test, uint32_t against){
	if (test != against){
		printf("[Failed] Expected: %d ", against);
		printf("got: %d.\n", test);
		return False;
	}
	return True;
}

void DisplayBytes(uint8_t* bytes, uint32_t count){
	printf("[");
	for (uint32_t i = 0; i < count; i++){
		printf("%02x", bytes[i]);
		if (i < count - 1){
			printf(",");
		}
	}
	printf("]");
}
