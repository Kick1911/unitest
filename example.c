#include <unitest.h>
#include <stdio.h>

int main(void){
	TEST_F(kick){
		T_ASSERT(1 == 0);
	}TEST(kick);

	TEST_F(helloworld){
		T_ASSERT(1 < 0);
	}TEST(helloworld);

	TEST_F(foo){
		T_ASSERT(1 > 0);
	}TEST(foo);
	
	T_CONCLUDE();
	return 0;
}
