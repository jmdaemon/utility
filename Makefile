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

# Compiler Flags:
# -MM : Output single header dependencies for the compile files
# -MG : Run without being able to run into headers gcc can't find
# -MF : Write header dependencies to a file
COMPILE=gcc -c
LINK=gcc
DEPEND=gcc -MM -MG -MF
CFLAGS=-I. -I$(PATHU) -I$(PATHS) -I$(INCLUDES) -DTEST

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
# Unit Tests
#

# Note: Our files will be named:
# [source].c, test_[source].c
# Due to these substitutions they must be named like this
# in order for the tests to work and compile
RESULTS = $(patsubst $(PATHT)test_%.c,$(PATHR)test_%.txt,$(SRCT) )

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

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

test: $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"


# Rules for finding source files in sub directories

# Create test results
$(PATHR)%.txt: $(PATHB)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

# Link unit tests with the unity test framework and our sources
$(PATHB)test_%.$(TARGET_EXTENSION): $(PATHO)test_%.o $(PATHO)%.o $(PATHU)unity.o
	$(LINK) -o $@ $^

# Compile unity sources
$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

# Compile files in src directory
$(PATHO)%.o:: $(PATHS)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

# Compile files in test directory
$(PATHO)%.o:: $(PATHT)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

# Create a depends directory
$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

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

# Build paths

# Create build/
$(PATHB):
	$(MKDIR) $(PATHB)

# Create build/depends
$(PATHD):
	$(MKDIR) $(PATHD)

# Create build/objs
$(PATHO):
	$(MKDIR) $(PATHO)

# Create build/results
$(PATHR):
	$(MKDIR) $(PATHR)

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

# Remove output files for tests
clean-test:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt

# Keep test results & output
.PRECIOUS: $(PATHB)test_%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt
