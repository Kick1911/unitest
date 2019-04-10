include Makefile.in

example.test: example.c unitest.h
	gcc -ansi example.c -o example.test -I.
install:
	cp unitest.h -t $(ROOT)/include
clean:
	rm -f example.test a.out
