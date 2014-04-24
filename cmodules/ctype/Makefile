
CC = gcc
LD = $(CC)
CFLAGS =
LDFLAGS =

all : test-ctype

test-ctype : ctype.o test-ctype.o
	$(LD) $(LDFLAGS) -o $@ $^
	
clean :
	$(RM) *.o test-ctype
