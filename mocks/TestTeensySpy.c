#include "unity.h"
#include "TeensySpy.h"

void setUp(void)
{
  TeensySpy_Create();
}

void tearDown(void)
{
}

void test_TeensySpy_on_create(void)
{
  TEST_ASSERT_EQUAL_HEX16(LED_ID_UNKNOWN, TeensySpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, TeensySpy_GetLastState());
}

void test_TeensySpy_set_pinMode_to_Output(void)
{
  pinMode(5, OUTPUT);
  TEST_ASSERT_EQUAL_HEX16(5, TeensySpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(OUTPUT, TeensySpy_GetLastState());
}

