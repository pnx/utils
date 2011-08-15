
CFLAGS = -DMYDOWN_GLOBAL_COOKIE=./cookie.txt -DMYDOWN_SSL=1
LDFLAGS = -lssl
PROGRAM = qlxmpp

.phony = distclean clean

$(PROGRAM) : quakelivexmpp.o mydownlib.o
	$(CC) $(LDFLAGS) -o $@ $^

clean :
	$(RM) *.o

distclean : clean
	$(RM) $(PROGRAM)
