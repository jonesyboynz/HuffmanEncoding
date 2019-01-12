#include "Test.h"
#include "../../Framework/Framework.h"

#define SETUP(x) SETUP_BASE(); BitArray* bitArray = NewBitArray(x)
#define TEARDOWN(x) Destroy(bitArray); TEARDOWN_BASE()

bool Can_create_bit_array_test();

bool Bit_array_max_length_is_correct();

bool Can_get_and_set_bits();

bool Can_add_bits();

bool Can_remove_bits();

bool Array_limits_work();

bool Array_copy_works();

bool Array_append_works();

bool Array_append_final_bit_correct();

bool Array_append_limit();

bool Array_clear_works();

bool Push_byte_slice_is_correct_1();

bool Push_byte_slice_is_correct_2();

bool Push_byte_slice_works_at_limits();

TestSet* Bit_array_test_set(){
	TestSet* set = NewTestSet("Bit array tests");
	AddTest(set, NewTest("Can create bit array", Can_create_bit_array_test, False));
	AddTest(set, NewTest("Max length is correct", Bit_array_max_length_is_correct, False));
	AddTest(set, NewTest("Can get and set bits", Can_get_and_set_bits, False));
	AddTest(set, NewTest("Can push bits", Can_add_bits, False));
	AddTest(set, NewTest("Can pop bits", Can_remove_bits, False));
	AddTest(set, NewTest("Limits work", Array_limits_work, False));
	AddTest(set, NewTest("Copy works", Array_copy_works, False));
	AddTest(set, NewTest("Append works", Array_append_works, False));
	AddTest(set, NewTest("Append final bit is correct", Array_append_final_bit_correct, False));
	AddTest(set, NewTest("Cannot append more bits than array size", Array_append_limit, False));
	AddTest(set, NewTest("Clear works", Array_clear_works, False));
	AddTest(set, NewTest("Push byte slice is correct 1", Push_byte_slice_is_correct_1, False));
	AddTest(set, NewTest("Push byte slice is correct 2", Push_byte_slice_is_correct_2, False));
	AddTest(set, NewTest("Push byte slice is correct at limits", Push_byte_slice_works_at_limits, False));
	return set;
}

bool Can_create_bit_array_test(){
	BitArray* bitArray = NewBitArray(8);
	bool result = AssertNotNull(bitArray);
	Destroy(bitArray);
	return result;
}

bool Bit_array_max_length_is_correct(){
	BitArray* bitArray1 = NewBitArray(3);
	BitArray* bitArray2 = NewBitArray(32);
	BitArray* bitArray3 = NewBitArray(63);
	bool result = AssertEquals(bitArray1->MaxCount, 8);
	result &= AssertEquals(bitArray2->MaxCount, 32);
	result &= AssertEquals(bitArray3->MaxCount, 64);
	Destroy(bitArray1);
	Destroy(bitArray2);
	Destroy(bitArray3);
	return result;
}

bool Can_get_and_set_bits(){
	BitArray* bitArray = NewBitArray(16);
	SetBit(bitArray, 7, BIT1);
	bool result = AssertEquals(GetBit(bitArray, 7), BIT1);
	result &= AssertEquals(bitArray->Count, 8);
	Destroy(bitArray);
	return result;
}

bool Can_add_bits(){
	BitArray* bitArray = NewBitArray(16);
	for (uint8_t i = 0; i < 16; i++){
		PushBit(bitArray, i % 2);
	}
	bool result = AssertEquals(bitArray->Count, 16);
	result &= AssertEquals(bitArray->Bits[0], 0x55);
	result &= AssertEquals(bitArray->Bits[1], 0x55);
	Destroy(bitArray);
	return result;
}

bool Can_remove_bits(){
	SETUP(16);
	for (uint8_t i = 0; i < 16; i++){
		PushBit(bitArray, i % 2);
	}
	TEST_FOR(AssertEquals(PopBit(bitArray), BIT1));
	TEST_FOR(AssertEquals(PopBit(bitArray), BIT0));
	TEST_FOR(AssertEquals(bitArray->Count, 14));
	TEARDOWN();
}

bool Array_limits_work(){
	SETUP(30); //max should be 32.
	TEST_FOR(AssertEquals(PopBit(bitArray), BIT_ERROR));
	for (uint8_t i = 0; i < 32; i++){
		PushBit(bitArray, i % 2);
	}
	TEST_FOR(AssertFalse(PushBit(bitArray, BIT1)));
	TEST_FOR(AssertEquals(bitArray->Count, 32));
	TEARDOWN();
}

bool Array_copy_works(){
	BitArray* bitArray = NewBitArray(16);
	for (uint8_t i = 0; i < 16; i++){
		PushBit(bitArray, i % 2);
	}
	BitArray* bitArrayCopy = Copy(bitArray);
	bool result = AssertEquals(bitArray->MaxCount, bitArrayCopy->MaxCount);
	result &= AssertEquals(bitArray->Count, bitArrayCopy->Count);
	for (uint8_t i = 0; i < 2; i++){
		result &= AssertEquals(bitArray->Bits[i], bitArrayCopy->Bits[i]);
	}
	Destroy(bitArray);
	Destroy(bitArrayCopy);
	return result;
}

bool Array_append_works(){
	BitArray* bitArray1 = NewBitArray(16);
	BitArray* bitArray2 = NewBitArray(16);
	for (uint8_t i = 0; i < 16; i++){
		PushBit(bitArray1, i % 2);
	}
	bool result = AssertEquals(Append(bitArray2, bitArray1), bitArray1->MaxCount);
	for (uint8_t i = 0; i < bitArray1->MaxCount; i++){
		result &= AssertEquals(GetBit(bitArray1, i), GetBit(bitArray2, i));
	}
	Destroy(bitArray1);
	Destroy(bitArray2);
	return result;
}

bool Array_append_final_bit_correct(){
	BitArray* bitArray1 = NewBitArray(8);
	BitArray* bitArray2 = NewBitArray(8);
	BitArray* bitArray3 = NewBitArray(32);
	for (uint8_t i = 0; i < 8; i++){
		PushBit(bitArray1, BIT1);
		PushBit(bitArray2, BIT0);
	}
	bool result = AssertEquals(Append(bitArray3, bitArray1), 8);
	result &= AssertEquals(Append(bitArray3, bitArray2), 8);
	result &= AssertEquals(Append(bitArray3, bitArray1), 8);
	result &= AssertEquals(bitArray3->Bits[0], 0xFF);
	result &= AssertEquals(bitArray3->Bits[1], 0x00);
	result &= AssertEquals(bitArray3->Bits[2], 0xFF);
	Destroy(bitArray1);
	Destroy(bitArray2);
	Destroy(bitArray3);
	return result;
}

bool Array_append_limit(){
	BitArray* bitArray1 = NewBitArray(16);
	BitArray* bitArray2 = NewBitArray(16);
	for (uint8_t i = 0; i < 16; i++){
		PushBit(bitArray1, i % 2);
	}
	for (uint8_t i = 0; i < 5; i++){
		PushBit(bitArray2, i % 2);
	}
	bool result = AssertEquals(Append(bitArray2, bitArray1), 16 - 5);
	Destroy(bitArray1);
	Destroy(bitArray2);
	return result;
}

bool Array_clear_works(){
	SETUP(16);
	for (uint8_t i = 0; i < 16; i++){
		PushBit(bitArray, i % 2);
	}
	Clear(bitArray);
	TEST_FOR(AssertEquals(bitArray->Count, 0));
	for (uint8_t i = 0; i < bitArray->MaxCount / BITS_IN_BYTE; i++){
		TEST_FOR(AssertEquals(bitArray->Bits[i], 0x00));
	}
	TEARDOWN();
}

bool Push_byte_slice_is_correct_1(){
	SETUP(16);
	TEST_FOR(AssertEquals(PushByteSlice(bitArray, 0x3c, 2, 6), 4));
	TEST_FOR(AssertEquals(bitArray->Bits[0], 0xF0));
	TEARDOWN();
}

bool Push_byte_slice_is_correct_2(){ //TODO
	SETUP(16);
	TEST_FOR(AssertEquals(PushByteSlice(bitArray, 0x3c, 2, 6), 4));
	TEST_FOR(AssertEquals(bitArray->Bits[0], 0xF0));
	TEARDOWN();
}

bool Push_byte_slice_works_at_limits(){
	SETUP(8);
	TEST_FOR(AssertEquals(PushByteSlice(bitArray, 0xFF, -1, -8), 0));
	TEST_FOR(AssertEquals(PushByteSlice(bitArray, 0xFF, 10, 19), 0));
	TEST_FOR(AssertEquals(PushByteSlice(bitArray, 0xFF, 0, 8), 8));
	TEST_FOR(AssertEquals(PushByteSlice(bitArray, 0xFF, 0, 8), 0));
	TEARDOWN();
}