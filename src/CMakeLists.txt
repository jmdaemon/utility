set(HEADERS ${INCLUDES_DIR})

set(TARGET utility)

set(LIB_NAME ${TARGET})
add_library(${LIB_NAME}
    SHARED # Build as a dynamic library
    file.c
    command.c)
target_include_directories(${LIB_NAME} PUBLIC ${HEADERS})

set(LIB_NAME ${TARGET}_static)
add_library(${LIB_NAME}
    STATIC # Build as a static library
    file.c
    command.c)
target_include_directories(${LIB_NAME} PUBLIC ${HEADERS})
#set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "${INCLUDES_DIR}/bytesize.h")
#target_link_libraries(${LIB_NAME} PRIVATE)
