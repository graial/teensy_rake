// TestModule4.cpp correctly prefixed, should be recognized by Rakefile

#include "unity.h"
#include "Module1.h"
#include "other_module.h"

extern "C"{
	void setUp(void)
	{
	}

	void tearDown(void)
	{
	}
	void test_TestModule4_has_an_empty_test(void)
	{
		TEST_PASS();
	}
}