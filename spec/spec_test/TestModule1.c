// TestModule1.c correctly prefixed, should be recognized by Rakefile

#include "unity.h"
#include "Module1.h"
#include "other_module.h"

void test_TestModule1_has_an_empty_test(void)
{
	TEST_PASS();
}