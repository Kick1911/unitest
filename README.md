# unitest

A unit testing framework for C. Written in 100% C89 ISO preprocessor code.

# Usage
I have designed this library to be easy-to-use. No init function needed (though, I am considering adding one). A `T_CONCLUDE` is needed at the end for final report and returning an error code if need be.

## Start testing
You can add all your code as the second parameter of the `TEST` macro.
```C
TEST(Integer tests,
		long int a = 1 << 31;
		long int b = a*a;
		T_ASSERT(1 == 1);
		T_ASSERT_NUM(1, 1);
		T_ASSERT_NUM(b, a*a);
);
```
or simply call a function in the second parameter.

## Setup
A setup function can be added as follows:
```C
void setup(void** args);
T_SETUP(&setup);
```
The function should receive `void**` and return `void`.
By default you can 10 pointers to `args`. This can be changed with the definition, `T_SETUP_RESULT_SIZE`.
To access `args` in your test, use `T_SETUP_RESULT`.
To stop running the setup function, simply:
```C
T_SETUP(0);
```

## Teardown
You are responsible for deallocating all the memory you put into `T_SETUP_RESULT`.
The prototype for the teardown function follows the setup function. Adding the function is also similar.

## Test reporters
### Spec
This is the default reporter.

TODO: Add image
### List
To enable this reporter, compile with `-DT_REPORTER_LIST=1` argument.

TODO: Add image
### Dot
Looks like the python `unittest` reporter. To enable this reporter, compile with `-DT_REPORTER_DOT=1` argument.

TODO: Add image

## Test Suites
Test suites are done as follows, but of course you may substitute the second arguments for functions if you want to.
```C
T_SUITE(Binary operations,
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
```