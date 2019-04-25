#include <unitest.h>
#include <stdio.h>
#include <string.h>

void print(char* a){
	printf("%s\n", a);
}

int main(void){
	TEST(kick,
		char a[] = "Kick";
		char b[] = "Ness";
		T_ASSERT(1 == 0);
		T_ASSERT_STRING(a, b);
	);

	TEST(helloworld,
		T_ASSERT(1 < 0);
		T_ASSERT_NUM(1, 0);
	);

	TEST(foo, 
		T_ASSERT(1 > 0);
		T_ASSERT_STRING("Kickness", "Kickness");
	);

	TEST(Print something, print("g"));
	
	T_CONCLUDE();
	return 0;
}
