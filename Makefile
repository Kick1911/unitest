include Makefile.in
CFLAGS=$(DEBUG) -ansi -pedantic -Wall -Wno-deprecated-declarations

example_dot.test: example.c unitest.h suite.c
	$(CC) $(CFLAGS) example.c -o example_dot.test -I. -DT_REPORTER_DOT=1
example_spec.test: example.c unitest.h suite.c
	$(CC) $(CFLAGS) example.c -o example_spec.test -I.
test: example_dot.test example_spec.test
	valgrind ./example_spec.test && valgrind ./example_dot.test
install:
	cp unitest.h -t $(ROOT)/include
clean:
	rm -f *.test a.out

.PHONY: clean install test