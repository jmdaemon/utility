cmake_minimum_required(VERSION 3.12)

project(
    utility
    VERSION 1.6.0
    DESCRIPTION "General purpose C utility library"
    LANGUAGES C)

if (NOT USE_AS_SUBPROJECT)
    # Variable Toggles
    set(NO_COLOR OFF CACHE INTERNAL "Toggles colored output errors")
    set(BUILD_DOC ON CACHE INTERNAL "Build documentation")
    set(ENABLE_LOGGING OFF CACHE INTERNAL "View the logging statements/debug info")
    set(LOG_LEVEL 0 CACHE INTERNAL "Enable only specific log levels")
endif()

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if (EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with "
                        "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                        "remove CMakeCache.txt and CMakeFiles.")
endif()

# Include CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/" "${PROJECT_SOURCE_DIR}/cmake")

if (NO_COLOR)
    # Don't use colored output
else()
    # Include colored output by default
    include(Color)
endif()

# Include header files
set(INCLUDES_DIR "${PROJECT_SOURCE_DIR}/include")
set(HEADERS_VERSION "${PROJECT_BINARY_DIR}/include")

# Include dependencies
include(Library)

# Specify project dependencies
# PKG_DEPENDS: Library names to link the output files
# DEB_DEPENDS: Debian packages that provide the libraries the project depends upon
set(PKG_DEPENDS pcre)
set(DEB_DEPENDS libc pcre)

# Add subdirectories
subdirs(subprojects src)

if (BUILD_TESTING AND NOT USE_AS_SUBPROJECT)
    include(Unity)
    include(CTest)
    add_subdirectory(test)
endif()

if (NOT USE_AS_SUBPROJECT)
    # Generate automatic docs with Doxygen
    include(Docs)

    # Install build artifacts system-wide
    include(Install)

    # Packages
    include(InstallRequiredSystemLibraries)
    include(Debian)
endif()
