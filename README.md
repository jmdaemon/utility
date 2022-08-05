# Utility

General purpose C utility library

## Goals

### File

The goals of `file` are simple. The library must

- Be able to handle file sizes > 2GiB
- Be compatible on at least Windows and Linux (ideally more).
- Optionally offer useful variants that may be faster, or safer.
- Must also build on Windows.

## Building

To build this project run:

```
make lib
```

There should be a library `libutility.so` in `build/release/lib/`.

Then you can include your dependency into your project like so


## Make

For Make you can include this library into your build system with:

Note that this assumes utility is in a `subprojects` directory.

``` Make
CFLAGS = ... -Isubprojects/utility/include
LDFLAGS = -Lsubprojects/utility/build/release/lib -llibutility
```

## CMake

This assumes that utility is in subprojects directory.

You can add utility with:

``` CMake
set(UTILITY_HEADERS subprojects/utility/include)
set(UTILITY_LIB subprojects/utility/build/release/lib)
find_library(utility
             NAMES utility
             HINTS ${UTILITY_LIB})

if(NOT utility)
  message(FATAL_ERROR "Utility library not found!")
endif()

target_include_directories(${PROJECT_EXECUTABLE} PUBLIC ${UTILITY_HEADERS})
target_link_libraries(${PROJECT_EXECUTABLE} utility)
```
