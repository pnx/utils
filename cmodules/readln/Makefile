
CC = gcc
CFLAGS = -g
LD = $(CC)
LDFLAGS =

all : test

test : test.o readln.o
	$(LD) $(LDFLAGS) -o $@ $^

clean :
	$(RM) *.o

distclean : clean
	$(RM) test
