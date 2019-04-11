#include <unitest.h>
#include <stdio.h>

int main(void){
	TEST(kick, a(){
		T_ASSERT(1 == 0);
		T_ASSERT_STRING("Kick", "Ness");
	});

	TEST(helloworld,
		T_ASSERT(1 < 0);
		T_ASSERT_NUM(1, 0);
	);

	TEST(foo, 
		T_ASSERT(1 > 0);
		T_ASSERT_STRING("Kickness", "Kickness");
	);
	
	T_CONCLUDE();
	return 0;
}
