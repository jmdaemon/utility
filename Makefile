.SECONDEXPANSION:

include make/os.mk
include make/structure.mk
include make/config.mk

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

include make/install.mk

# 
# Rules
#

.PHONY: subprojects clean

subprojects: 

# Build as a library
include make/library.mk

install-lib-headers:
	install $(PATHI)/file.h $(DESTDIR)$(PREFIX)/include/file.h
	install $(PATHI)/command.h $(DESTDIR)$(PREFIX)/include/command.h
	install $(PATHI)/utility.h $(DESTDIR)$(PREFIX)/include/utility.h

uninstall-lib-headers:
	$(CLEANUP) $(DESTDIR)$(PREFIX)/include/file.h
	$(CLEANUP) $(DESTDIR)$(PREFIX)/include/command.h
	$(CLEANUP) $(DESTDIR)$(PREFIX)/include/utility.h

#
# Other rules
#

clean: clean-test clean-lib clean-subprojects clean-objs
