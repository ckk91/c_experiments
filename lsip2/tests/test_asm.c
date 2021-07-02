#include "minunit.h"
#include "../src/reader.h"
#include "../src/asm.h"

int tests_run = 0;


char* make_stream(char *c) {
	FILE *fstream = fmemopen(c, strlen(c), "r");

	char* s = read_string_from_input(fstream);
	fclose(fstream);

    return s;
}

// vm opstack has atoms, lists

static char*
test_cons() {
	char* s = make_stream("(CONS 1 NIL)");
    /*
    [1,NIL] => [(1 NIL)]
    NIL
    LOADC 1
    CONS
    APPLY
    */
	size_t pos = 0;
    value *v = read_expr(s, &pos);
}


static char* all_tests() {
	// mu_run_test(test_read_string_from_input);
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