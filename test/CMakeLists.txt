set(HEADERS ${INCLUDES_DIR} ${HEADERS_UNITY})
set(TEST_DEPS unity utility_static)

# Note that if you want to include more tests, create an executable and add them with add_test()

# Copy files required for running tests manually (`./test_[test_name]`)
file(COPY ../LICENSE DESTINATION ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build/results)

# utility/file
set(TARGET file)
set(TEST_NAME test_${TARGET})
add_executable(${TEST_NAME} test_file.c)
target_link_libraries(${TEST_NAME} PRIVATE ${TEST_DEPS})
target_include_directories(${TEST_NAME} PUBLIC ${HEADERS})
add_test(
    NAME ${TEST_NAME}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMAND ${TEST_NAME})

# utility
set(TARGET utility)
set(TEST_NAME test_${TARGET})
add_executable(${TEST_NAME} test_utility.c)
target_link_libraries(${TEST_NAME} PRIVATE ${TEST_DEPS})
target_include_directories(${TEST_NAME} PUBLIC ${HEADERS})
add_test(
    NAME ${TEST_NAME}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMAND ${TEST_NAME})
