/*
Defines some macros for setting up and tearing down tests.
*/

#ifndef SETUP_TEARDOWN_H
#define SETUP_TEARDOWN_H

#define TEST_RESULT_VARIABLE_NAME() test_result_macro


//Setup should include this as the first statement.
#define SETUP_BASE() bool TEST_RESULT_VARIABLE_NAME = True


//Teardown should include this as a final statement.
#define TEARDOWN_BASE() return TEST_RESULT_VARIABLE_NAME


//User can repeatedly TEST_FOR(case).
#define TEST_FOR(x) TEST_RESULT_VARIABLE_NAME &= x

#endif