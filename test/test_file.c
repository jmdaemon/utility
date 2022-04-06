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

void file_size_should_be_under_4gib() {
    const off_t limit  = 1024 * 1024 * 4;
    const bool result = under_limit("LICENSE", limit);
    TEST_ASSERT_TRUE(result);
}

void read_file_should_not_be_null() {
    /* Read file shouldn't be null on files 
    that exist */
    char* contents = read_file("LICENSE");
    /*printf("Contents:\n%s", contents);*/
    TEST_ASSERT_NOT_NULL(contents);
    /* Since we allocated memory with malloc
       we must free the pointer here */
    free(contents);
}

void read_slice_should_not_be_null() {
    char* contents = read_slice("LICENSE", 300, 400);
    printf("Contents:\n%s\n", contents);
    TEST_ASSERT_NOT_NULL(contents);
    /* Since we allocated memory with malloc
       we must free the pointer here */
    free(contents);
}

void write_file_should_not_be_null() {
    const char* path = "build/results/example.txt";
    /* Remove previous runs */
    FILE* examplep = fopen(path, "rb");
    if (examplep != NULL) {
        fclose(examplep);
        puts("Deleting previous example.txt file\n");
        int success = remove(path);
        if (success == 0)
            printf("Deleted %s\n", path);
        else
            printf("Unable to delete %s\n", path);

    }
    const char* contents = "This file should not be null";
    write_file(path, contents);
    FILE* fp = fopen(path, "rb");
    TEST_ASSERT_TRUE(file_exists(fp));
    fclose(fp);
}

/* Add tests for big files >4 GiB here */

/* Main runner */
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(file_size_should_return_correct_size);
    RUN_TEST(file_exists_should_return_true);
    RUN_TEST(file_size_should_be_under_4gib);
    RUN_TEST(read_file_should_not_be_null);
    RUN_TEST(read_slice_should_not_be_null);
    RUN_TEST(write_file_should_not_be_null);
    return UNITY_END();
}
