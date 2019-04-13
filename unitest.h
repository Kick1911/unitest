#ifndef UNITEST
#define UNITEST

#define T_SET_COLOUR(stream, colour) fprintf(stream, "\033[0;"#colour"m");
#define T_RESET_COLOUR(stream) fprintf(stream, "\033[0m");
#define FAILED(msg) \
		T_FLAG = 1; \
		T_SET_COLOUR(stderr, 31); \
		fprintf(stderr, "Failed %s:%d: %s\n", __FILE__, __LINE__, #msg); \
		T_RESET_COLOUR(stderr)

/** This Macro does not work with common seperated initialising statements */
#define TEST(name, code) T_FLAG = 0; T_COUNT++; \
					printf("TEST: %s\n", #name); \
					{code} \
					if(!T_FLAG){ \
						T_SET_COLOUR(stdout, 32); \
						printf("PASSED\n"); \
						T_RESET_COLOUR(stdout); \
						T_PASSED++; \
					} \
					printf("\n")

#define T_ASSERT(statement) \
	if(!(statement)){ FAILED(statement); }

#define T_ASSERT_STRING(a, b, s) \
	if(strncmp((a), (b), (s))){ FAILED(a != b); }

#define T_ASSERT_NUM(a, b) \
	if((a) != (b)){ FAILED(a != b); }

#define T_CONCLUDE() \
		printf("%d/%d PASSED\n", T_PASSED, T_COUNT);

char T_FLAG;
int T_COUNT = 0;
int T_PASSED = 0;

#endif
