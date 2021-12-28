#include "unity.h"
#include "FakeTimeService.h"

void setUp(void)
{
  TimeService_Create();
}

void test_FakeTimeService_on_create(void)
{
  Time time;
  TimeService_GetTime(&time);
  TEST_ASSERT_EQUAL_HEX16(MILLISECONDS_UNKNOWN, time.milliseconds);
}

void test_FakeTimeService_sets_time(void)
{
  Time time;
  FakeTimeService_SetMilliseconds(77);
  TimeService_GetTime(&time);
  TEST_ASSERT_EQUAL_HEX16(77, time.milliseconds);
}