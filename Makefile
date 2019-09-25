include Makefile.in
REPORTERS = dot list spec
EXE = $(REPORTERS:%=example_%.test)
CFLAGS=$(DEBUG) -ansi -pedantic -Wall -Wno-deprecated-declarations

$(EXE): example.c unitest.h suite.c
	$(eval UPPER := $(shell echo '$(@:example_%.test=%)' | tr a-z A-Z))
	$(CC) $(CFLAGS) $< -o $@ -I. -DT_REPORTER_$(UPPER)=1

test: $(EXE)
	@for exe in $(EXE) ; do \
		valgrind --error-exitcode=1 --leak-check=full ./$$exe ; \
	done

install:
	cp unitest.h -t $(ROOT)/include
clean:
	rm -f *.test a.out

.PHONY: clean install test