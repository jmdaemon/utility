set(HEADERS ${INCLUDES_DIR})
set(TARGET utility)
set(SRCS utility.c file.c command.c)

make_ssl(
    NAME ${TARGET}
    SRCS ${SRCS}
    HDRS ${HEADERS}
    DEPS ${PKG_DEPENDS})

# Manual Install

install(TARGETS # Shared library
    ${TARGET} DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    COMPONENT lib)

install(TARGETS # Static library
    ${TARGET}_static DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    COMPONENT lib)
