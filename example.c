#include <unitest.h>
#include <stdio.h>
#include <string.h>

int main(void){
	TEST(kick,
		char a[] = "Kick";
		char b[] = "Ness";
		T_ASSERT(1 == 0);
		T_ASSERT_STRING(a, b, strlen(a));
	);

	TEST(helloworld,
		T_ASSERT(1 < 0);
		T_ASSERT_NUM(1, 0);
	);

	TEST(foo, 
		T_ASSERT(1 > 0);
		T_ASSERT_STRING("Kickness", "Kickness", strlen("Kickness"));
	);
	
	T_CONCLUDE();
	return 0;
}
