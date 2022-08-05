set(HEADERS ${INCLUDES_DIR} ${HEADERS_UNITY})

# Note that if you want to include more tests, create an executable and add them with add_test()

# Set up our first and only test suite
set(LIB_NAME utility)

set(TARGET file)
set(TEST_NAME test_${TARGET})

# Build the test code and runner
add_executable(${TEST_NAME} test_file.c)
target_link_libraries(${TEST_NAME}
    ${LIB_NAME}_static
    unity)
target_include_directories(${TEST_NAME} PUBLIC ${HEADERS})

# Add main test runner
add_test(test_${TARGET} ${TEST_NAME})

# Create needed files for tests
file(COPY ../LICENSE DESTINATION ${CMAKE_BINARY_DIR}/test)
file(MAKE_DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/test/build/results) # Must exist at build time

# These files are needed when running ctest -V manually
file(COPY ../LICENSE DESTINATION ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/build/results)
