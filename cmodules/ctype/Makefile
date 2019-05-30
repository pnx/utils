
CC = gcc
LD = $(CC)
CFLAGS =
LDFLAGS =

all : test

test : ctype.o test.o
	$(LD) $(LDFLAGS) -o $@ $^

clean :
	$(RM) *.o test
