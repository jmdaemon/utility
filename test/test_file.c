#include "unity.h"
#include <sys/stat.h>
#include <stdio.h>

#include "file.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void file_size_should_return_correct_size() {
    const off_t result = file_size("LICENSE");
    printf("Result: %ld\n", result);
    const off_t expected = 34524;
    printf("Expected: %ld\n", expected);
    TEST_ASSERT_TRUE(result == expected);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(file_size_should_return_correct_size);
    return UNITY_END();
}
