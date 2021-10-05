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

void test_TeensySpy_wont_respond_to_digitalWriteFast_if_no_pinMode_call(void)
{
  pinMode(5, OUTPUT);
  digitalWriteFast(8, HIGH);

  TEST_ASSERT_EQUAL_HEX16(LED_ID_UNKNOWN, TeensySpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, TeensySpy_GetLastState());
}

void test_TeensySpy_set_a_pin_to_HIGH(void)
{
  pinMode(8, OUTPUT);
  digitalWriteFast(8, HIGH);

  TEST_ASSERT_EQUAL_HEX16(8, TeensySpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_ON, TeensySpy_GetLastState());
}

void test_TeensySpy_set_a_pin_to_LOW(void)
{
  pinMode(8, OUTPUT);
  digitalWriteFast(8, LOW);

  TEST_ASSERT_EQUAL_HEX16(8, TeensySpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_OFF, TeensySpy_GetLastState());
}