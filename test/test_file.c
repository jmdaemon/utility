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
    off_t filesize = file_size("../LICENSE");
    printf("%ld\n", filesize);
    TEST_ASSERT_TRUE(filesize == 34);
    TEST_ASSERT_TRUE(filesize == 0);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(file_size_should_return_correct_size);
    return UNITY_END();
}
