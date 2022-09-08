#include "utility.h"
#include "unity.h"

void setUp(void) {
    /* set stuff up here */
}

void tearDown(void) {
    /* clean stuff up here */
}

void ltimestamp_should_return_correct_time() {
    // Get the current time
    time_t rawtime = get_time();
    struct tm * ptm;
    ptm = gmtime (&rawtime);

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(ltimestamp_should_return_correct_time);
    return UNITY_END();
}
