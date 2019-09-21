#ifndef UNITEST
#define UNITEST

#define T_SETUP_RESULT_SIZE (10)

#define T_FAIL_COLOUR (31)
#define T_PASS_COLOUR (32)

#define _T_DO_NOTHING do {} while(0)

#ifdef T_REPORTER_LIST
#elif T_REPORTER_DOT
    #define T_PASS_DOT_COLOUR (90)
	#define _T_SUITE_TITLE(msg) _T_DO_NOTHING

	#define _T_TEST_FAIL_MSG(msg, a, b, title) \
		T_SET_COLOUR(stderr, T_FAIL_COLOUR); \
		fprintf(stderr, "!"); \
		T_RESET_COLOUR(stderr)

	#define _T_TEST_PASS_MSG(title) \
		T_SET_COLOUR(stdout, T_PASS_DOT_COLOUR); \
		fprintf(stdout, "."); \
		T_RESET_COLOUR(stdout)

	#define _T_CONCLUDE() \
		fprintf(stdout, "\n\n"); \
		T_SET_COLOUR(stdout, T_PASS_COLOUR); \
		fprintf(stdout, "%d passing\n", T_PASSED); \
		T_RESET_COLOUR(stdout); \
		if(T_PASSED < T_COUNT){ \
			T_SET_COLOUR(stdout, T_FAIL_COLOUR); \
			fprintf(stdout, "%d failing\n", T_COUNT - T_PASSED); \
			T_RESET_COLOUR(stdout); \
			return 1; \
		}
#else
	/** T_REPORTER_SPEC as default */
	#define _T_SUITE_TITLE(msg) \
		T_PRINTF_1(stdout, "%s\n", msg)

	#define _T_TEST_FAIL_MSG(msg, a, b, title) \
		char* p; \
		char* format; \
		size_t err_msg_size; \
		char header[] = "✘ [%s] %s:%d: "; \
		err_msg_size = strlen(header) + strlen(#msg) + 2; \
		format = malloc(sizeof(char) * err_msg_size); \
		T_SET_COLOUR(stderr, T_FAIL_COLOUR); \
		strcpy(format, header); \
		p = format + strlen(header); \
		strcpy(p, #msg); \
		p += strlen(#msg); \
		strcpy(p, "\n"); \
		format[err_msg_size - 1] = 0; \
		T_PRINTF_5(stderr, format, title, __FILE__, __LINE__, (a), (b)); \
		free(format); \
		T_RESET_COLOUR(stderr)

	#define _T_TEST_PASS_MSG(title) \
		T_SET_COLOUR(stdout, T_PASS_COLOUR); \
		T_PRINTF(stdout, "✔"); \
		T_RESET_COLOUR(stdout); \
		fprintf(stdout, " %s\n", title)

	#define _T_CONCLUDE() \
		T_SET_COLOUR(stdout, T_PASS_COLOUR); \
		if(T_PASSED < T_COUNT){ \
			T_SET_COLOUR(stdout, T_FAIL_COLOUR); \
			fprintf(stdout, "✘ %d/%d failed\n", T_PASSED, T_COUNT); \
			T_RESET_COLOUR(stdout); \
			return 1; \
		} \
		fprintf(stdout, "✔ %d/%d passed\n", T_PASSED, T_COUNT); \
		T_RESET_COLOUR(stdout)
#endif

#define T_SET_COLOUR(stream, colour) fprintf(stream, "\033[1;%dm", colour)
#define T_RESET_COLOUR(stream) fprintf(stream, "\033[0m")

#define _PRINTF_INDENT(stream) \
	{ \
		int i = T_PRINT_LEVEL; \
		while(i--){ fprintf(stream, "   "); } \
	}

#define T_PRINTF(stream, format) \
	_PRINTF_INDENT(stream); \
	fprintf(stream, format)
#define T_PRINTF_1(stream, format, n1) \
	_PRINTF_INDENT(stream); \
	fprintf(stream, format, n1)
#define T_PRINTF_2(stream, format, n1, n2) \
	_PRINTF_INDENT(stream); \
	fprintf(stream, format, n1, n2)
#define T_PRINTF_3(stream, format, n1, n2, n3) \
	_PRINTF_INDENT(stream); \
	fprintf(stream, format, n1, n2, n3)
#define T_PRINTF_4(stream, format, n1, n2, n3, n4) \
	_PRINTF_INDENT(stream); \
	fprintf(stream, format, n1, n2, n3, n4)
#define T_PRINTF_5(stream, format, n1, n2, n3, n4, n5) \
	_PRINTF_INDENT(stream); \
	fprintf(stream, format, n1, n2, n3, n4, n5)
#define T_PRINTF_6(stream, format, n1, n2, n3, n4, n5, n6) \
	_PRINTF_INDENT(stream); \
	fprintf(stream, format, n1, n2, n3, n4, n5, n6)

#define T_SUITE(msg, code) \
	_T_SUITE_TITLE(#msg); \
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

#define T_FAILED(msg, a, b, title) \
	_T_TEST_FAIL_MSG(msg, a, b, title); \
	T_FLAG = 1;

#define T_PASSED(title) \
	_T_TEST_PASS_MSG(title); \
	T_PASSED++

/** This Macro does not work with common seperated initialising statements */
#define TEST(title, code) NEG_FLAG = 1; MAIN_TEST(title, code)
#define N_TEST(title, code) NEG_FLAG = 0; MAIN_TEST(title, code)

#define MAIN_TEST(title, code) T_FLAG = 0; T_COUNT++; \
	{ \
		char _title[] = #title; \
		void** _SETUP_RESULT = NULL; \
        _title[0] = _title[0]; /** Making Compiler happy when var not used */ \
		if(T_SETUP_FUNC){ \
			_SETUP_RESULT = (void**)malloc(sizeof(void*) * T_SETUP_RESULT_SIZE); \
			T_SETUP_FUNC(_SETUP_RESULT); \
		} \
		{code;} \
		if(T_TEARDOWN_FUNC){ T_TEARDOWN_FUNC(_SETUP_RESULT); } \
		free(_SETUP_RESULT); \
		if(!T_FLAG){ \
			T_PASSED(_title); \
		} \
	}

#define ASSERT(statement, op1, op2, format) \
	if(!!(statement) ^ NEG_FLAG){ T_FAILED(format, op1, op2, _title); }

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

#define T_SETUP(func) T_SETUP_FUNC = func
#define T_TEARDOWN(func) T_TEARDOWN_FUNC = func
#define T_SUITE_SETUP(func) T_SUITE_SETUP_FUNC = func
#define T_SUITE_TEARDOWN(func) T_SUITE_TEARDOWN_FUNC = func
#define T_CONCLUDE _T_CONCLUDE

typedef void (*_test_function_t)(void**);
char T_FLAG, NEG_FLAG;
int T_COUNT = 0, T_PASSED = 0, T_PRINT_LEVEL = 0;
_test_function_t T_SETUP_FUNC = 0, T_SUITE_SETUP_FUNC = 0;
_test_function_t T_TEARDOWN_FUNC = 0, T_SUITE_TEARDOWN_FUNC = 0;

#endif
