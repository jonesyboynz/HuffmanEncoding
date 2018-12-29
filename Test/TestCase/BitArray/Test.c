#include "Test.h"
#include "../../Framework/Framework.h"

bool Can_create_bit_array_test();

bool Bit_array_max_length_is_correct();

bool Can_add_bits();

bool Can_remove_bits();

bool Array_limits_work();

bool Array_copy_works();

TestSet* Bit_array_test_set(){
	TestSet* set = NewTestSet("Bit array tests");
	AddTest(set, NewTest("Can create bit array", Can_create_bit_array_test, False));
	AddTest(set, NewTest("Max length is correct", Bit_array_max_length_is_correct, False));
	AddTest(set, NewTest("Can add bits", Can_add_bits, False));
	AddTest(set, NewTest("Can remove bits", Can_remove_bits, False));
	AddTest(set, NewTest("Limits work", Array_limits_work, False));
	AddTest(set, NewTest("Copy works", Array_copy_works, False));
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
	BitArray* bitArray = NewBitArray(16);
	for (uint8_t i = 0; i < 16; i++){
		PushBit(bitArray, i % 2);
	}
	bool result = AssertEquals(PopBit(bitArray), BIT1);
	result &= AssertEquals(PopBit(bitArray), BIT0);
	result &= AssertEquals(bitArray->Count, 14);
	Destroy(bitArray);
	return result;
}

bool Array_limits_work(){
	BitArray* bitArray = NewBitArray(30); //max should be 32.
	bool result = AssertEquals(PopBit(bitArray), BIT_ERROR);
	for (uint8_t i = 0; i < 32; i++){
		PushBit(bitArray, i % 2);
	}
	result &= AssertFalse(PushBit(bitArray, BIT1));
	result &= AssertEquals(bitArray->Count, 32);
	Destroy(bitArray);
	return result;
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