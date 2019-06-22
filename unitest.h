#ifndef UNITEST
#define UNITEST

#define T_SET_COLOUR(stream, colour) fprintf(stream, "\033[0;"#colour"m")
#define T_RESET_COLOUR(stream) fprintf(stream, "\033[0m")
#define FAILED(msg, a, b) \
		T_FLAG = 1; \
		T_SET_COLOUR(stderr, 31); \
		fprintf(stderr, "Failed %s:%d: "#msg"\n", __FILE__, __LINE__, (a), (b)); \
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
					{code;} \
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
	if(sizeof((a)) == sizeof(float)){ \
		ASSERT((a) == (b), (a), (b), "%f != %f"); \
	}else if(sizeof((a)) == sizeof(double)){ \
		ASSERT((a) == (b), (a), (b), "%lf != %lf"); \
	}

#define T_CONCLUDE() \
		printf("%d/%d PASSED\n", T_PASSED, T_COUNT); \
		if(T_PASSED < T_COUNT) return 1;

char T_FLAG, NEG_FLAG;
int T_COUNT = 0;
int T_PASSED = 0;

#endif
