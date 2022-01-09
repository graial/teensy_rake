#include "unity.h"
#include "TimeService.h"
#include "TeensySpy.h"

void setUp(void)
{
  TeensySpy_Create();
}

void tearDown(void)
{
  // TeensySpy_Destroy();
}

void test_TimeService_GetTime_0_on_init(void)
{
  Time time;
  TimeService_GetTime(&time);
  TEST_ASSERT_EQUAL_HEX16(0, time.milliseconds);
}

void test_TimeService_GetTime_after_advancing_spy(void)
{
  Time time;
  TeensySpy_AdvanceElapsedMillis(85);
  TimeService_GetTime(&time);
  TEST_ASSERT_EQUAL_HEX16(85, time.milliseconds);
}