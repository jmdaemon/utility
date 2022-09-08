#include "utility.h"
#include "unity.h"

void setUp(void) { }
void tearDown(void) { }

void ltimestamp_should_return_correct_time() {
    // Get the current time
    time_t t = time(NULL);
    struct tm lt = {0};
    localtime_r(&t, &lt);

    // Ensure the time is correct
    printf("Offset to GMT is %lds.\n", lt.tm_gmtoff);
    printf("The time zone is '%s'.\n", lt.tm_zone);
    printf("Time: %2d:%02d.\n", lt.tm_hour, lt.tm_min);

    // Test format of ltimestamp
    char expect[6];
    sprintf(expect, "%2d:%02d", lt.tm_hour, lt.tm_min);
    const char* result = ltimestamp(get_time());
    TEST_ASSERT_EQUAL_STRING(expect, result);
    free((void*) result);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(ltimestamp_should_return_correct_time);
    return UNITY_END();
}
