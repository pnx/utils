
CC = gcc
LD = $(CC)
CFLAGS = -Werror -g
LDFLAGS =

all : test

test : crc32-test.o crc32.o
	$(LD) $(LDFLAGS) -o $@ $^

clean :
	$(RM) *.o

distclean : clean
	$(RM) test

