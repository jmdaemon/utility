set(HEADERS ${INCLUDES_DIR})

set(TARGET utility)
set(SRCS utility.c file.c command.c)

set(LIB_NAME ${TARGET})         # Build as a dynamic library
add_library(${LIB_NAME} SHARED ${SRCS})
target_include_directories(${LIB_NAME} PUBLIC ${HEADERS})

set(LIB_NAME ${TARGET}_static)  # Build as a static library
add_library(${LIB_NAME} STATIC ${SRCS})
target_include_directories(${LIB_NAME} PUBLIC ${HEADERS})
