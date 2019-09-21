#define _GNU_SOURCE
#include <unitest.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <suite_functions.c>

void print(char* a){
	printf("%s\n", a);
}

void setup(void** args){
	/** Set args - limited to 10 args */
	args[0] = "I am Kick";
	args[1] = malloc(sizeof(char));
}

void teardown(void** args){
	/** Free all args */
	free(args[1]);
}

int main(void){
	FILE* save_stderr;
	char* buffer;
	size_t size;

	N_TEST(Negative testing,
		long int a = 1 << 31;
		long int b = a*a;
		char n[] = "Kick";
		char m[] = "Ness";

		T_ASSERT(1 < 0);
		T_ASSERT_NUM(1, 0);
		T_ASSERT_NUM(b, 0);

		T_ASSERT_STRING(n, m);
	);

	TEST(String tests,
		char a[] = "nbionob <F9>82r32h9nrwn 9h489h 4<F9><F10><F3><F2>niom o";
		char b[] = "nbionob <F9>82r32h9nrwn 9h489h 4<F9><F10><F3><F2>niom o";
		T_ASSERT_STRING(a, b);
		T_ASSERT_STRING("Kickness", "Kickness");
	);

	TEST(Integer tests,
		long int a = 1 << 31;
		long int b = a*a;
		T_ASSERT(1 == 1);
		T_ASSERT_NUM(1, 1);
		T_ASSERT_NUM(b, a*a);
	);

	T_SETUP(&setup);
	T_TEARDOWN(&teardown);

	TEST(Setup,
		T_ASSERT_STRING((char*)_SETUP_RESULT[0], "I am Kick");
	);

	TEST(Pointer tests,
		char* a = NULL;
		char* b = NULL;
		a = malloc(sizeof(char) * 5);
		strcpy(a, "Kick");
		T_ASSERT(a);
		T_ASSERT(!b);
		free(a);
	);

	TEST(Floating point tests,
		T_ASSERT_FLOAT(0.5, 0.5f);
		T_ASSERT_FLOAT((float) 22/7, (float) 22/7);
		T_ASSERT_FLOAT((double) 22/7, (double) 22/7);
	);

	T_SETUP(0);
	T_TEARDOWN(0);

	TEST(Disable setup,
		T_ASSERT(!_SETUP_RESULT);
	);

    save_stderr = stderr;
    stderr = open_memstream(&buffer, &size);
	TEST(Failing tests,
		T_ASSERT_NUM(1, 0);
		T_ASSERT_CHAR('a', 'b');
		T_ASSERT_FLOAT(0.465, 458.1375);
		T_ASSERT_STRING("Not", "Equal");
		T_ASSERT(5 == 9);
	);
	T_PASSED++;

	fclose(stderr);
	#ifdef __clang__
		free(stderr);
	#endif
	printf("%s\n", buffer);
	stderr = save_stderr;

	/** Formatter tests */
    #ifdef T_REPORTER_LIST
    #elif T_REPORTER_DOT
		TEST(Failed messages,
			int count = 0;
			char* ptr = buffer;
            ptr = strchr(ptr, '!');
			while(ptr){
				T_ASSERT(ptr);
				ptr = strchr(ptr+1, '!');
				count++;
			}
			T_ASSERT_NUM(count, 5);
		);
	#else
	/** T_REPORTER_SPEC */
	{
		char* failed_msgs[] = {"\"1 != 0\"",
							"\"a != b\"",
							"\"0.465000 != 458.137500\"",
							"\"Not != Equal\"", "5 == 9", NULL};
		char* start = buffer,
			**ptr = failed_msgs,
			*end;
		while(*ptr){
			char* ts = *ptr;
			TEST(Failed messages,
				end = strchr(start, '\n');
				*end = 0;
				T_ASSERT(strstr(start, ts));
				start = end+1;
			);
			ptr++;
		}
	}
	#endif
	#include <suite.c>

	free(buffer);
	T_CONCLUDE();
	return 0;
}
