include make/os.mk

#
# Directories
#
# build/depends, build/objs, build/results are all used for building the unit tests

PATHU = subprojects/unity/src/
PATHS = src/
PATHT = test/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

INCLUDES = include/

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

SRCT = $(wildcard $(PATHT)*.c)

#
# Compile options
#

CFLAGS = -Wall -Wextra
LDFLAGS = 

include make/unity.mk

#
# Library
#

CFLAGS_LIB = -fPIC -g
LDFLAGS_LIB = -shared
LIB_SRCS = file.c command.c
LIB_OBJS = $(LIB_SRCS:.c=.o)
LIB = libutility.so
LIB_PREFIX = lib


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

# Create build/{debug, release} paths
BUILD_PATH = $(PATHB)$(TARGET)

# Library build settings
# -------------
# LIBRARY_FLAGS: 	Library flags in release or debug configuration
# BUILD_PATHL: 		The directory of the target library (build/{debug,release}/lib)
# BUILD_LIB_OBJS: The object files of the library target (build/{debug,release}/*.o)

LIBRARY_FLAGS = $(LDFLAGS) $(TARGET_FLAGS) $(CFLAGS_LIB) $(LDFLAGS_LIB) 

BUILD_PATHL = $(BUILD_PATH)/$(LIB_PREFIX)
BUILD_LIB = $(BUILD_PATHL)/$(LIB)
BUILD_LIB_OBJS = $(addprefix $(BUILD_PATH)/, $(LIB_OBJS))

# 
# Rules
#

# Unit Tests

.PHONY: clean clean-test clean-lib test lib 

#
# Library Builds
#

# Make the build paths for the library
lib: $(BUILD_PATHL) $(BUILD_LIB)

# Compiles the shared library target and its object files
$(BUILD_LIB): $(BUILD_LIB_OBJS) 
	$(CC) $(CFLAGS) $(LIBRARY_FLAGS) -o $@ $^

# Compile all object targets in $(BUILD_PATH)
$(BUILD_PATH)/%.o: $(PATHS)%.c
	$(CC) -c $(CFLAGS) $(TARGET_FLAGS) -o $@ $<

#
# Other rules
#

# Create build/{debug, release}
$(BUILD_PATH):
	$(MKDIR) $(BUILD_PATH)

# Create build/{debug, release}/lib
$(BUILD_PATHL):
	$(MKDIR) $(BUILD_PATHL)

clean: clean-test clean-lib

clean-lib:
	$(CLEANUP) $(BUILD_LIB)
	$(CLEANUP) $(BUILD_LIB_OBJS)
