#include <unitest.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

void print(char* a){
	printf("%s\n", a);
}

void setup(void** args){
	/** Set args - limited to 10 args */
	printf("SET EM' UP!!\n");
	args[0] = "I am Kick";
}

void teardown(void** args){
	/** Free all args */
	printf("KNOCK EM' DOWN!\n");
}

int main(void){
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

	T_SETUP(setup);
	T_TEARDOWN(teardown);

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

	TEST(Print 'g', print("g"));
	
	T_CONCLUDE();
	return 0;
}
