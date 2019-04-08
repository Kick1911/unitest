example.test: example.c unitest.h
	gcc -ansi example.c -o example.test -I.
clean:
	rm -f example.test a.out
