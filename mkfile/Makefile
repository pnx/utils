
CC 	   = gcc
CFLAGS = -O2 -Wall
PREFIX = /usr/local/bin/

.PHONY = install clean

mkfile : mkfile.c
	$(CC) $(CFLAGS) $< -o $@

install : mkfile
	cp mkfile $(PREFIX)

clean : 
	$(RM) mkfile
