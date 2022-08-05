cmake_minimum_required(VERSION 3.12)

project(
    utility
    VERSION 1.0.0
    DESCRIPTION "General purpose C utility library"
    LANGUAGES C)

# Add option to build documentation. On by default
option(BUILD_DOC "Build documentation" ON)

# Use colored output
if (NOT COLOR)
    # Don't use colored output
else()
    # Include colored output by default
    include(Color)
endif()

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with "
                        "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                        "remove CMakeCache.txt and CMakeFiles.")
endif()

# Include CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/" "${PROJECT_SOURCE_DIR}/cmake")

# Include header files
set(INCLUDES_DIR "${PROJECT_SOURCE_DIR}/include")
set(HEADERS_VERSION "${PROJECT_BINARY_DIR}/include")
if(BUILD_TESTING)
    message(STATUS "Setting \$\{HEADERS_UNITY\}")
    set(HEADERS_UNITY "${PROJECT_SOURCE_DIR}/subprojects/unity/src")
endif()

# Include dependencies
include(FetchContent)
include(Unity)
#include(logc)

# Add subdirectories
add_subdirectory(subprojects)
add_subdirectory(src)

if(BUILD_TESTING)
    include(CTest)
    add_subdirectory(test)
endif()

# Documentation
# Check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    file(COPY Doxyfile DESTINATION ${CMAKE_BINARY_DIR})
    message("Doxygen build started")

    # Ensure that build/docs is created
    file(MAKE_DIRECTORY DESTINATION ${PROJECT_SOURCE_DIR}/build/docs)

    # Note the option ALL builds the docs together with the other targets
    add_custom_target(doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

# Manual Installs
# Set default manual installation directory to /usr/local
set(CMAKE_INSTALL_PREFIX /usr/local)

# Manual Uninstall Target
# Usage:
# cmake uninstall .
# sudo make uninstall or sudo ninja uninstall
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake)
endif()

if ((TARGET uninstall) AND (EXISTS "${LOC_PATH}"))
    message(FATAL_ERROR
        "You cannot uninstall in the source directory."
        "You may only uninstall from the build subdirectory."
        "Feel free to remove remove CMakeCache.txt and CMakeFiles.")
endif()

# Packages
include(InstallRequiredSystemLibraries)
include(Debian)
