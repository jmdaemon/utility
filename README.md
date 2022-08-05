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

### Make

To build with make:

``` bash
make release lib
```

This creates `build/release/libutility.so`.

To install the library:

``` bash
sudo make install
```

This installs the library to `/usr/local/`, if you want to install to `/usr/` instead, run:

``` bash
PREFIX=/usr/ sudo make install 
```

If you want to uninstall the library:

``` bash
sudo make uninstall
```

### CMake

To build with CMake:
``` bash
cmake --preset gcc-release-unix-makefiles
cd build/gcc-debug-unix-makefiles
make
```

To install the library:

``` bash
sudo cmake --install .
```

This installs the library to `/usr/local/`, if you want to install to `/usr/` instead, run:

``` bash
sudo cmake --install --prefix /usr
```

If you want to uninstall the library:

``` bash
cmake uninstall .
sudo make uninstall
```

## Using as a Subproject

If you are building Utility directly as a subproject in your build system.
See below for more details.

## Make
To integrate with a Makefile project. Be sure to include the
library's headers in `include` with `-Iutility/include` during compilation,
and link to Utility with `-llibutility`.

## CMake

You can include `Utility` by using FetchContent:
``` cmake
FetchContent_Declare(utility
    GIT_REPOSITORY  https://github.com/jmdaemon/utility)
FetchContent_MakeAvailable(${LIB_NAME})
```

Or, if you are bundling it directly in your project:
``` cmake
add_subdirectory("subprojects/utility")
```
Note that this method assumes that the source is in a directory called `subprojects/utility`.
