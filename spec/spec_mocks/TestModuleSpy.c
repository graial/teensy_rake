// TestModuleSpy.c is correcly prefixed with Test, it should be recognized by the Rakefile
#include "unity.h"
#include "other_module.h"

void test_TestModuleSpy_has_an_empty_test(void)
{
	TEST_PASS();
}