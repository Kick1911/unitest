#ifndef UNITEST
#define UNITEST

#define SETUP_RESULT_SIZE (10)

#define T_SET_COLOUR(stream, colour) fprintf(stream, "\033[0;"#colour"m")
#define T_RESET_COLOUR(stream) fprintf(stream, "\033[0m")
#define FAILED(msg, a, b) \
		char header[] = "Failed %s:%d: "; \
		char* format = malloc(sizeof(char) * (strlen(header) + strlen(#msg) + 2)); \
		T_FLAG = 1; \
		T_SET_COLOUR(stderr, 31); \
		strcpy(format, header); \
		strcpy(format, #msg"\n"); \
		format[strlen(header) + strlen(#msg) + 1] = 0; \
		fprintf(stderr, format, __FILE__, __LINE__, (a), (b)); \
		free(format); \
		T_RESET_COLOUR(stderr)

#define PASSED(msg) \
		T_SET_COLOUR(stdout, 32); \
		printf("PASSED %s\n", msg); \
		T_RESET_COLOUR(stdout); \
		T_PASSED++

/** This Macro does not work with common seperated initialising statements */
#define TEST(name, code) NEG_FLAG = 1; MAIN_TEST(POSITIVE, name, code)
#define N_TEST(name, code) NEG_FLAG = 0; MAIN_TEST(NEGATIVE, name, code)

#define MAIN_TEST(title, name, code) T_FLAG = 0; T_COUNT++; \
					printf(#title" TEST: %s\n", #name); \
					{ \
						void** _SETUP_RESULT = (void**)malloc(sizeof(void*) * SETUP_RESULT_SIZE); \
						if(T_SETUP_FUNC){ T_SETUP_FUNC(_SETUP_RESULT); }\
						{code;} \
						if(T_TEARDOWN_FUNC){ T_TEARDOWN_FUNC(_SETUP_RESULT); }\
						free(_SETUP_RESULT); \
					} \
					if(!T_FLAG){ \
						PASSED(""); \
					} \
					printf("\n")

#define ASSERT(statement, op1, op2, format) \
	if(!!(statement) ^ NEG_FLAG){ FAILED(format, op1, op2); }

#define T_ASSERT(statement) \
	ASSERT(statement, #statement, "", "%s%s")

#define T_ASSERT_STRING(a, b) \
	ASSERT(!strcmp((a), (b)), (a), (b), "%s != %s")

#define T_ASSERT_NUM(a, b) \
	if(sizeof((a)) <= sizeof(int)){ \
		ASSERT((a) == (b), (a), (b), "%d != %d"); \
	}else if(sizeof((a)) == sizeof(long)){ \
		ASSERT((a) == (b), (a), (b), "%ld != %ld"); \
	}

#define T_ASSERT_FLOAT(a, b) \
	ASSERT((a) == (b), (a), (b), "%f != %f"); \

#define T_CONCLUDE() \
		printf("%d/%d PASSED\n", T_PASSED, T_COUNT); \
		if(T_PASSED < T_COUNT){ return 1; }

#define T_SETUP(func) T_SETUP_FUNC = &func
#define T_TEARDOWN(func) T_TEARDOWN_FUNC = &func

char T_FLAG, NEG_FLAG;
int T_COUNT = 0;
int T_PASSED = 0;
void (*T_SETUP_FUNC)(void**) = 0;
void (*T_TEARDOWN_FUNC)(void**) = 0;
#endif
