include make/os.mk
include make/structure.mk

#
# Compile options
#

GLOBAL_CFLAGS = -Wall -Wextra
GLOBAL_LDFLAGS = 

# Include headers
INCLUDES = -I. -I$(PATHI)

include make/unity.mk

#
# Library
#

#CFLAGS_LIB = -fPIC -g
#LDFLAGS_LIB = -shared

#LIB_SRCS = file.c command.c
#LIB_OBJS = $(LIB_SRCS:.c=.o)
#LIB = libutility.so
#LIB_PREFIX = lib

LIBRARY_SRCS = file.c command.c
LIBRARY_OBJS = $(LIBRARY_SRCS:.c=.o)
LIBRARY_NAME = libutility.so

#LIB_PREFIX = lib

include make/install.mk
include make/config.mk


#
# Build settings
# 

# Release build settings
# Set release to default configuration
TARGET:=release
TARGET_FLAGS:= -O3 -DNDEBUG $(LDFLAGS)

# Debug build settings
# Set debug as an optional switch
ifeq ($(filter debug,$(MAKECMDGOALS)),debug)
TARGET=debug
TARGET_FLAGS= -g -O0 -DDEBUG $(LDFLAGS)
endif

# 
# Rules
#

.PHONY: all subprojects clean

subprojects: 

# SP_DEPENDS : Object files to be included into lib, bin targets
# SP_INCLUDES: Header files to be included into lib,bin
SP_DEPENDS =                                                    # Unit Tests
SP_INCLUDES =
.PHONY: clean clean-test clean-lib test lib 

# Build as a library
include make/library.mk

#
# Other rules
#

clean: clean-test clean-lib
