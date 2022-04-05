#include "file.h"
#include "unity.h"

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

void file_exists_should_return_true() {
    FILE* fp = fopen("LICENSE", "rb");
    const bool result = file_exists(fp);
    fclose(fp);
    const bool expected = true;
    TEST_ASSERT_TRUE(result == expected);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(file_size_should_return_correct_size);
    RUN_TEST(file_exists_should_return_true);
    return UNITY_END();
}
