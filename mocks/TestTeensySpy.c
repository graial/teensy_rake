#include "unity.h"
#include "TeensySpy.h"
#include "Arduino.h"

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
  digitalWriteFast(5, HIGH);

  TEST_ASSERT_EQUAL_HEX16(LED_ID_UNKNOWN, TeensySpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, TeensySpy_GetLastState());
}

void test_TeensySpy_set_a_pin_to_HIGH(void)
{
  pinMode(8, OUTPUT);
  digitalWriteFast(8, HIGH);

  TEST_ASSERT_EQUAL_HEX16(8, TeensySpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(HIGH, TeensySpy_GetLastState());
}

void test_TeensySpy_set_a_pin_to_LOW(void)
{
  pinMode(8, OUTPUT);
  digitalWriteFast(8, HIGH);
  digitalWriteFast(8, LOW);

  TEST_ASSERT_EQUAL_HEX16(8, TeensySpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LOW, TeensySpy_GetLastState());
}

void test_TeensySpy_stubs_0_elapsedMillis_on_init(void)
{
  TEST_ASSERT_EQUAL_HEX16(0, TeensySpy_GetElapsedMillis());
}

void test_TeensySpy_stubs_can_advance_elapsedMillis(void)
{
  TeensySpy_AdvanceElapsedMillis(50);
  TEST_ASSERT_EQUAL_HEX16(50, TeensySpy_GetElapsedMillis());
}

void test_TeensySpy_stubs_can_reset_elapsedMillis(void)
{
  TeensySpy_AdvanceElapsedMillis(50);
  TeensySpy_ResetElapsedMillis();
  TEST_ASSERT_EQUAL_HEX16(0, TeensySpy_GetElapsedMillis());
}