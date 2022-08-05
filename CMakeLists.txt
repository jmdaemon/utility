cmake_minimum_required(VERSION 3.12)

project(
    utility
    VERSION 1.0.0
    DESCRIPTION "General purpose C utility library"
    LANGUAGES C)

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
