.SECONDEXPANSION:

include make/os.mk
include make/structure.mk
include make/config.mk
include make/install.mk
include make/templates.mk

VERSION_MAJOR = 1
VERSION_MINOR = 14
VERSION_PATCH = 0

#
# Compile options
#

GLOBAL_CFLAGS = -Wall -Wextra
GLOBAL_LDFLAGS = -lpcre

# Include headers
INCLUDES = -I. -I$(PATHI)

#
# Subprojects
#
# SP_DEPENDS : Object files to be included into lib, bin targets
# SP_INCLUDES: Header files to be included into lib,bin

include make/unity.mk

#
# Library
#

LIBRARY_SRCS = file.c command.c utility.c
LIBRARY_OBJS = $(LIBRARY_SRCS:.c=.o)
LIBRARY_NAME = libutility.so


# 
# Rules
#

.PHONY: subprojects clean

subprojects: 

# Build as a library
include make/library.mk

# Build documentation
include make/docs.mk

# Install/Uninstall rules
install-subprojects: $(INSTALL_SP_TARGET)
uninstall-subprojects: $(UNINSTALL_SP_TARGET)

# Clean specific output files
clean: $(CLEAN_TARGET)
clean-subprojects: $(CLEAN_SP_TARGET)
