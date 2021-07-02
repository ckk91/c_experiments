#include <stdio.h>
#include <string.h>

#include "minunit.h"
#include "../src/env.h"


int tests_run = 0;

static char* test_make_env(){
	value* env = make_env(NULL);

	mu_assert("parent not empty", env->cdr == NULL);
	mu_assert("no cell", env->tag == _CELL);
	
	value* new_env = make_env(env);
	mu_assert("new env and parent equal", env != new_env);

}
static char* test_env_pop(){}
static char* test_env_add(){}
static char* test_find_in_env(){}



static char* all_tests() {
	mu_run_test(test_make_env);
	// mu_run_test(test_read_symbol);
	// mu_run_test(test_read_expr);  // dotted
	return 0;
}

int main(int argc, char const* argv[])
{
	char* result = all_tests();
	if (result != 0)
	{
		printf("%s\n", result);
	}
	else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);
	return result != 0;
}
