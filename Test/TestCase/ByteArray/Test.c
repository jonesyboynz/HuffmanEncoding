#include "Test.h"

bool Can_create_byte_array();

bool Can_push_bytes();

bool Can_pop_bytes();

bool Can_union_arrays();

bool Cannot_push_bytes_when_array_full();

bool Cannot_pop_bytes_when_array_empty();

TestSet* Byte_array_test_set(){
	TestSet* set = NewTestSet("Byte array tests");
	AddTest(set, NewTest("Can create byte array", Can_create_byte_array, False));
	AddTest(set, NewTest("Can push bytes", Can_push_bytes, False));
	AddTest(set, NewTest("Can pop bytes", Can_pop_bytes, False));
	AddTest(set, NewTest("Can add arrays together", Can_union_arrays, False));
	AddTest(set, NewTest("Cannot push to full array", Cannot_push_bytes_when_array_full, False));
	AddTest(set, NewTest("Cannot pop from empty array", Cannot_pop_bytes_when_array_empty, False));
	return set;
}

bool Can_create_byte_array(){
	ByteArray* array = NewByteArray(512);
	bool result = AssertNotNull(array);
	DestroyByteArray(array);
	return result;
}

bool Can_push_bytes(){
	ByteArray* array = NewByteArray(512);
	bool result = True;
	for (uint16_t i = 0; i < array->MaxCount; i++)
	{
		result &= PushByte(array, i);
	}
	for (uint16_t i = 0; i < array->Count; i++)
	{
		result &= AssertEquals(array->Data[i], i % 256);
	}
	DestroyByteArray(array);
	return result;
}

bool Can_pop_bytes(){
	ByteArray* array = NewByteArray(512);
	bool result = True;
	for (uint16_t i = 0; i < array->MaxCount; i++)
	{
		result &= PushByte(array, i);
	}
	for (uint16_t i = 0; i < array->Count; i++)
	{
		result &= AssertEquals(PopByte(array), 255 - i % 256);
	}
	DestroyByteArray(array);
	return result;
}

bool Can_union_arrays(){
	bool result = True;
	ByteArray* array1 = NewByteArray(512);
	ByteArray* array2 = NewByteArray(512);
	for (uint16_t i = 0; i < array1->MaxCount; i++)
	{
		result &= PushByte(array1, i);
	}
	for (uint16_t i = 0; i < array2->MaxCount; i++)
	{
		result &= PushByte(array2, i);
	}
	ByteArray* unionArray = Union(array1, array2);
	for (uint16_t i = 0; i < unionArray->Count; i++)
	{
		result &= AssertEquals(unionArray->Data[i], i % 256);
	}
	DestroyByteArray(array1);
	DestroyByteArray(array2);
	DestroyByteArray(unionArray);
	return result;
}

bool Cannot_push_bytes_when_array_full(){
	ByteArray* array = NewByteArray(10);
	for (uint16_t i = 0; i < array->MaxCount; i++)
	{
		PushByte(array, i);
	}
	bool result = AssertFalse(PushByte(array, 10));
	DestroyByteArray(array);
	return result;
}

bool Cannot_pop_bytes_when_array_empty(){
	ByteArray* array = NewByteArray(10);
	bool result = AssertEquals(PopByte(array), BYTE_ERROR);
	DestroyByteArray(array);
	return result;
}