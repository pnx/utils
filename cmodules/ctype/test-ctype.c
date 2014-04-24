
#include <stdio.h>
#include "ctype.h"

typedef int (*func_t)(int);

/* check functions */
static int check_upper(int c) { return c >= 'A' && c <= 'Z'; }
static int check_lower(int c) { return c >= 'a' && c <= 'z'; }
static int check_alpha(int c) { return check_upper(c) || check_lower(c); }
static int check_digit(int c) { return c >= '0' && c <= '9'; }
static int check_alnum(int c) { return check_alpha(c) || check_digit(c); }

/* test structure */
struct test {
	/* Name of the test. */
	const char *name; 

	/* Function to test. */
	func_t func;

	/* A Function known to be correct, 
	   return value will be checked against func */
	func_t check; 
};

#define DECL_FUNC(name) \
	static int func_ ## name(int c) { return is ## name(c); }

#define DECL_TEST(name) \
	{ #name, func_ ## name, check_ ## name }


/* Declare functions for all isX macros */
DECL_FUNC(upper);
DECL_FUNC(lower);
DECL_FUNC(alpha);
DECL_FUNC(alnum);
DECL_FUNC(digit);

/* Test function */
static void test(struct test *test) {

	int i;

	printf("%s test: ", test->name);

	for(i=0; i < 255; i++) {

		if (test->func(i) != test->check(i)) {
			printf("failed for '%c' (0x%x)\n", i, i);
			return;
		}
	}

	printf("passed\n");
}

int main() {

	int i;

	struct test tests[5] = {
		DECL_TEST(upper),
		DECL_TEST(lower),
		DECL_TEST(alpha),
		DECL_TEST(alnum),
		DECL_TEST(digit)
	};

	/* Run all tests */
	for(i=0; i < sizeof(tests) / sizeof(tests[0]); i++)
		test(&tests[i]);

	return 0;
}
