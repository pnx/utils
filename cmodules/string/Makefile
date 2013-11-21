
CC = gcc
CFLAGS = -g
LD = $(CC)
LDFLAGS =

all : test

test : tests.o strrev.o memcpy_sb.o
	$(LD) $(LDFLAGS) -o $@ $^

clean :
	$(RM) *.o

distclean : clean
	$(RM) test
