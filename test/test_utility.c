#include "utility.h"
#include "unity.h"

void setUp(void) {
    /* set stuff up here */
}

void tearDown(void) {
    /* clean stuff up here */
}

void ltimestamp_should_return_correct_time() {
    time_t t = time(NULL);
    struct tm lt = {0};

    localtime_r(&t, &lt);

    char* expect = (char*)malloc(5 * sizeof(char));
    sprintf(expect, "%2d:%02d", lt.tm_hour, lt.tm_min);

    printf("Offset to GMT is %lds.\n", lt.tm_gmtoff);
    printf("The time zone is '%s'.\n", lt.tm_zone);
    printf("Time: %2d:%02d.\n", lt.tm_hour, lt.tm_min);

    time_t rawtime = get_time();
    const char* result = ltimestamp(rawtime);

    TEST_ASSERT_EQUAL_STRING(expect, result);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(ltimestamp_should_return_correct_time);
    return UNITY_END();
}
