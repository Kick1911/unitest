#ifndef UNITEST
#define UNITEST

#define T_SETUP_RESULT_SIZE (10)
#define T_FAIL_MSG_STACK (255)
#define T_TEST_MSG_STACK (255)

#define T_SET_COLOUR(stream, colour) fprintf(stream, "\033[0;"#colour"m")
#define T_RESET_COLOUR(stream) fprintf(stream, "\033[0m")

#define T_PRINTF(stream, format) \
	fprintf(stream, format)
#define T_PRINTF_1(stream, format, n1) \
	fprintf(stream, format, n1)
#define T_PRINTF_2(stream, format, n1, n2) \
	fprintf(stream, format, n1, n2)
#define T_PRINTF_3(stream, format, n1, n2, n3) \
	fprintf(stream, format, n1, n2, n3)
#define T_PRINTF_4(stream, format, n1, n2, n3, n4) \
	fprintf(stream, format, n1, n2, n3, n4)
#define T_PRINTF_5(stream, format, n1, n2, n3, n4, n5) \
	fprintf(stream, format, n1, n2, n3, n4, n5)
#define T_PRINTF_6(stream, format, n1, n2, n3, n4, n5, n6) \
	fprintf(stream, format, n1, n2, n3, n4, n5, n6)

#define T_SUITE(msg, code) \
	T_PRINTF_1(stdout, "RUN TEST SUITE: %s\n\n", #msg); \
    T_PRINT_LEVEL++;  \
	{ \
        void** _SUITE_SETUP_RESULT = NULL; \
        if(T_SUITE_SETUP_FUNC){ \
            _SUITE_SETUP_RESULT = (void**)malloc(sizeof(void*) * T_SETUP_RESULT_SIZE); \
            T_SUITE_SETUP_FUNC(_SUITE_SETUP_RESULT); \
            T_SUITE_SETUP_FUNC = 0; \
        } \
		{code;} \
        if(T_SUITE_TEARDOWN_FUNC){ \
			T_SUITE_TEARDOWN_FUNC(_SUITE_SETUP_RESULT); \
			T_SUITE_TEARDOWN_FUNC = 0; \
		} \
        free(_SUITE_SETUP_RESULT); \
	} \
    T_PRINT_LEVEL--

#define FAILED(msg, a, b) \
	char* p; \
	char* format; \
	char* err_msg; \
	size_t err_msg_size; \
	char header[] = "Failed %s:%d: "; \
	char seperator[] = " - "; \
	err_msg = POP_ERR_MSG(); \
	err_msg_size = strlen(header) + strlen(#msg) + 2; \
	if(err_msg) err_msg_size += strlen(err_msg) + strlen(seperator); \
	format = malloc(sizeof(char) * err_msg_size); \
	T_FLAG = 1; \
	T_SET_COLOUR(stderr, 31); \
	strcpy(format, header); \
	p = format + strlen(header); \
	strcpy(p, #msg); \
	p += strlen(#msg); \
	if(err_msg){ \
		strcpy(p, seperator); \
		p += strlen(seperator); \
		strcpy(p, err_msg); \
		p += strlen(err_msg); \
	} \
	strcpy(p, "\n"); \
	format[err_msg_size - 1] = 0; \
	T_PRINTF_4(stderr, format, __FILE__, __LINE__, (a), (b)); \
	free(format); \
	T_RESET_COLOUR(stderr)

#define PASSED(msg) \
	T_SET_COLOUR(stdout, 32); \
	T_PRINTF_1(stdout, "PASSED %s\n", msg); \
	T_RESET_COLOUR(stdout); \
	T_PASSED++

/** This Macro does not work with common seperated initialising statements */
#define TEST(name, code) NEG_FLAG = 1; MAIN_TEST(POSITIVE, name, code)
#define N_TEST(name, code) NEG_FLAG = 0; MAIN_TEST(NEGATIVE, name, code)

#define MAIN_TEST(title, name, code) T_FLAG = 0; T_COUNT++; \
	T_PRINT_LEVEL++;  \
	{ \
		char* msg = POP_TEST_MSG(); \
		void** _SETUP_RESULT = NULL; \
		T_PRINTF_3(stdout, #title" TEST: %s%s%s\n", #name, (msg)?" - ":"", (msg)?msg:""); \
		if(T_SETUP_FUNC){ \
			_SETUP_RESULT = (void**)malloc(sizeof(void*) * T_SETUP_RESULT_SIZE); \
			T_SETUP_FUNC(_SETUP_RESULT); \
		} \
		{code;} \
		if(T_TEARDOWN_FUNC){ T_TEARDOWN_FUNC(_SETUP_RESULT); } \
		free(_SETUP_RESULT); \
	} \
	if(!T_FLAG){ \
		PASSED(""); \
	} \
	T_PRINT_LEVEL--;  \
	T_PRINTF(stdout, "\n")

#define ASSERT(statement, op1, op2, format) \
	if(!!(statement) ^ NEG_FLAG){ FAILED(format, op1, op2); }

#define T_ASSERT(statement) \
	ASSERT(statement, #statement, "", "%s%s")

#define T_ASSERT_STRING(a, b) \
	ASSERT(!strcmp((a), (b)), (a), (b), "%s != %s")

#define T_ASSERT_CHAR(a, b) \
	ASSERT((a) == (b), (a), (b), "%c != %c")

#define T_ASSERT_NUM(a, b) \
	if(sizeof((a)) <= sizeof(int)){ \
		ASSERT((a) == (b), (a), (b), "%d != %d"); \
	}else if(sizeof((a)) == sizeof(long)){ \
		ASSERT((a) == (b), (a), (b), "%ld != %ld"); \
	}

#define T_ASSERT_FLOAT(a, b) \
	ASSERT((a) == (b), (a), (b), "%f != %f")

#define T_CONCLUDE() \
	T_PRINTF_2(stdout, "%d/%d PASSED\n", T_PASSED, T_COUNT); \
	if(T_PASSED < T_COUNT){ return 1; }

#define T_ERR_MSG(msg) *_custom_fail_msgs = msg; _custom_fail_msgs++
#define POP_ERR_MSG() \
	(_custom_fail_msgs - _CUSTOM_FAIL_MSGS > 0)? *--_custom_fail_msgs: NULL

#define T_TEST_MSG(msg) *_custom_test_msgs = msg; _custom_test_msgs++
#define POP_TEST_MSG() \
	(_custom_test_msgs - _CUSTOM_TEST_MSGS > 0)? *--_custom_test_msgs: NULL

#define T_SETUP(func) T_SETUP_FUNC = func
#define T_TEARDOWN(func) T_TEARDOWN_FUNC = func
#define T_SUITE_SETUP(func) T_SUITE_SETUP_FUNC = func
#define T_SUITE_TEARDOWN(func) T_SUITE_TEARDOWN_FUNC = func

typedef void (*_test_function_t)(void**);
char T_FLAG, NEG_FLAG;
int T_COUNT = 0, T_PASSED = 0, T_PRINT_LEVEL = 0;
char* _CUSTOM_FAIL_MSGS[T_FAIL_MSG_STACK];
char** _custom_fail_msgs = _CUSTOM_FAIL_MSGS;
char* _CUSTOM_TEST_MSGS[T_TEST_MSG_STACK];
char** _custom_test_msgs = _CUSTOM_TEST_MSGS;
_test_function_t T_SETUP_FUNC = 0, T_SUITE_SETUP_FUNC = 0;
_test_function_t T_TEARDOWN_FUNC = 0, T_SUITE_TEARDOWN_FUNC = 0;

#endif
