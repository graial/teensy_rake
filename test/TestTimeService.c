#include "unity.h"
#include "TimeService.h"
#include "TeensySpy.h"

void setUp(void)
{
  TeensySpy_Create();
}

void tearDown(void)
{
}

void test_TimeService_GetTime_0_on_init(void)
{
  Time time;
  TimeService_GetTime(&time);
  TEST_ASSERT_EQUAL_HEX16(0, time.milliseconds);
}

// void test_TimeService_GetTime_after_advancing_spy(void)
// {
//   Time time;
//   TeensySpy_AdvanceElapsedMillis(85);
//   TimeService_GetTime(&time);
//   TEST_ASSERT_EQUAL_HEX16(85, time.milliseconds);
// }

// void test_TimeService_GetTime_triggers_callback_if_timeCounter_less_than_set_delay(void)
// {
//    TimeService_SetPeriodicAlarmInMilliseconds(10, testCallback);
//    TeensySpy_AdvanceElapsedMillis(8);
//    TimeService_CheckForPeriodicAlarm();
//    TEST_ASSERT_FALSE(TeensySpy_GetLastCallback());
// }

// void test_TimeService_GetTime_triggers_callback_if_timeCounter_exceeds_set_delay(void)
// {
//    TimeService_SetPeriodicAlarmInMilliseconds(10, testCallback);
//    TeensySpy_AdvanceElapsedMillis(12);
//    TimeService_CheckForPeriodicAlarm();
//    TEST_ASSERT_TRUE(TeensySpy_GetLastCallback());
// }

// void test_TimeService_Reset_sets_timeCounter_back_to_0(void)
// {
//    TimeService_SetPeriodicAlarmInMilliseconds(10, testCallback);
//    TeensySpy_AdvanceElapsedMillis(12);
//    TimeService_Reset();
//    TEST_ASSERT_EQUAL_HEX16(0, TeensySpy_GetElapsedMillis());
// }