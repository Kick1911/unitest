#ifndef UNITEST
#define UNITEST

#define ADD_TEST(func) tests[T_COUNT] = func; test_names[T_COUNT++] = #func


#define T_SET_COLOUR(stream, colour) fprintf(stream, "\033[0;"#colour"m");
#define T_RESET_COLOUR(stream) fprintf(stream, "\033[0m");
#define FAILED_MSG(msg) \
		T_SET_COLOUR(stderr, 31); \
		fprintf(stderr, "Failed %s:%d: %s\n", __FILE__, __LINE__, #msg); \
		T_RESET_COLOUR(stderr)
#define TEST_F(name) test_names[T_COUNT] = #name; \
					T_FLAG = 0; \
					printf("TEST: %s\n", #name); \
					void test_##name()
#define TEST(name) tests[T_COUNT++] = test_##name; \
					test_##name(); \
					if(!T_FLAG){ \
						T_SET_COLOUR(stdout, 32); \
						printf("PASSED\n"); \
						T_RESET_COLOUR(stdout); \
						T_PASSED++; \
					} \
					printf("\n")
#define T_ASSERT(statement) \
		if(!(statement)){ \
			FAILED_MSG(#statement); \
			T_FLAG = 1; \
		}
#define T_CONCLUDE() \
		printf("%d/%d PASSED\n", T_PASSED, T_COUNT); \

/* extern int T_COUNT;
extern void (*tests[256])();
extern const char* test_names[256]; */

char T_FLAG;
int T_COUNT = 0;
int T_PASSED = 0;
void (*tests[256])();
const char* test_names[256];

#endif
