include Makefile.in
CFLAGS=$(DEBUG) -ansi -pedantic -Wall -Wno-deprecated-declarations

example_dot.test: example.c unitest.h suite.c
	$(CC) $(CFLAGS) example.c -o $@ -I. -DT_REPORTER_DOT=1
example_list.test: example.c unitest.h suite.c
	$(CC) $(CFLAGS) example.c -o $@ -I. -DT_REPORTER_LIST=1
example_spec.test: example.c unitest.h suite.c
	$(CC) $(CFLAGS) example.c -o $@ -I.
test: example_dot.test example_spec.test example_list.test
	valgrind ./example_spec.test \
	&& valgrind ./example_dot.test \
	&& valgrind ./example_list.test
install:
	cp unitest.h -t $(ROOT)/include
clean:
	rm -f *.test a.out

.PHONY: clean install test