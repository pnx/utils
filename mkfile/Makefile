
CC	= gcc
CFLAGS	= -O2 -Wall
STRIP   = strip
PREFIX	= /usr/local/bin/

.PHONY	= install clean

ifdef DEBUG
CFLAGS += -g
STRIP :=
endif

mkfile : mkfile.c
	$(CC) $(CFLAGS) $< -o $@
ifdef STRIP
	$(STRIP) $@
endif

install : mkfile
	cp mkfile $(PREFIX)

clean :
	$(RM) mkfile
