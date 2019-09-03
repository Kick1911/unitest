include Makefile.in
CFLAGS=$(DEBUG) -ansi -pedantic -Wall -Wno-deprecated-declarations

example.test: example.c unitest.h
	cc $(CFLAGS) example.c -o example.test -I.
install:
	cp unitest.h -t $(ROOT)/include
clean:
	rm -f example.test a.out
