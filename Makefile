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

LIBRARY_SRCS = file.c command.c
LIBRARY_OBJS = $(LIBRARY_SRCS:.c=.o)
LIBRARY_NAME = libutility.so

include make/install.mk

#
# Build settings
# 

include make/config.mk

# 
# Rules
#

.PHONY: subprojects clean

subprojects: 

# SP_DEPENDS : Object files to be included into lib, bin targets
# SP_INCLUDES: Header files to be included into lib,bin
SP_DEPENDS =
SP_INCLUDES =

.PHONY: clean subprojects

# Build as a library
include make/library.mk

install-lib-headers:
	install $(PATHI)/file.h $(DESTDIR)$(PREFIX)/include/file.h
	install $(PATHI)/command.h $(DESTDIR)$(PREFIX)/include/command.h

uninstall-lib-headers:
	$(CLEANUP) $(DESTDIR)$(PREFIX)/include/file.h
	$(CLEANUP) $(DESTDIR)$(PREFIX)/include/command.h

#
# Other rules
#

clean: clean-test clean-lib
