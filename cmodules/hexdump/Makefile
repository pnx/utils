
CC = gcc
LD = $(CC)
CFLAGS = -Werror -g
LDFLAGS =

all : test

test : test.o hexdump.o
	$(LD) $(LDFLAGS) -o $@ $^

clean :
	$(RM) *.o

distclean : clean
	$(RM) test
