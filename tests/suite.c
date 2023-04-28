#include <unitest.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#ifdef MAIN
#include <suite_functions.c>
int main(void){
#endif

T_SUITE_SETUP(&suite_setup);
T_SUITE_TEARDOWN(&suite_teardown);
T_SUITE(String test,
    TEST(Character isEqual,
        char* ptr = SUITE_SETUP_RESULT[1];
        T_ASSERT_CHAR(*ptr, 'T');
    );
    TEST(String isEqual,
        T_ASSERT_STRING((char*)SUITE_SETUP_RESULT[0], "This is a test");
    );
);

T_SUITE(Binary operations,
    TEST(Setup and teardown disabled,
        /* Test teardown with valgrind */
        T_ASSERT(!T_SETUP_RESULT);
    );
    TEST(OR,
        T_ASSERT_NUM(1 | 0, 1);
    );
    TEST(XOR,
        T_ASSERT_NUM(1 ^ 0, 1);
    );
    TEST(AND,
        T_ASSERT_NUM(1 & 0, 0);
    );
    TEST(NOT,
        T_ASSERT_NUM(!1, 0);
    );
    TEST(TWOs compliment,
        T_ASSERT_NUM(~1, -2);
    );
);

T_SUITE(Decimal operations,
    TEST(Setup and teardown disabled,
        /* Test teardown with valgrind */
        T_ASSERT(!T_SETUP_RESULT);
    );
    TEST(Subtract,
        T_ASSERT_NUM(1 - 0, 1);
    );
    TEST(Multiply,
        T_ASSERT_NUM(1 * 0, 0);
    );
    TEST(Addition,
        T_ASSERT_NUM(-1 + 1, 0);
    );
    TEST(Division,
        T_ASSERT_FLOAT((double)1/5, (double)0.2);
    );
);

#ifdef MAIN
    T_CONCLUDE();
    return 0;
}
#endif
