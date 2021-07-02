#include <stdio.h>
#include <string.h>

#include "minunit.h"
#include "../src/reader.h"
#include "../src/printer.h"

int tests_run = 0;

static char* test_read_string_from_input(){
	char buffer[] = "hello";
	FILE *fstream = fmemopen(buffer, strlen(buffer), "r");

	char *s = read_string_from_input(fstream);

	fclose(fstream);
	
	
	mu_assert("stream read mismatch", strcmp(s, buffer) == 0);
	
}

char* make_stream(char *c) {
	FILE *fstream = fmemopen(c, strlen(c), "r");

	char* s = read_string_from_input(fstream);
	fclose(fstream);

    return s;
}

static char* test_read_symbol() {
	char* s = make_stream("SYMBOL FOO");
	size_t pos = 0;

	value *v = read_symbol(s, &pos);

	mu_assert("foo", v->tag == _SYM);
	mu_assert("string is not SYMBOL", strcmp(v->sym, "SYMBOL") == 0);
	// TODO test for internment
}
// todo test tokenize
static char* test_read_expr() {
	char* s = make_stream("(FOO BAR BAZ)");
	size_t pos = 0;
	
	int LEN = 2;  // 3 in total
    printf("TEST READ EXPR %zu\n", pos);
	value *v = read_expr(s, &pos);

	int i = 0;
	value* head = v;
	while (cdr(v) != NULL)
	{
		i++;
		v = cdr(v);
	}
	v = head;
	
	mu_assert("list not 3 long", i == LEN);

	mu_assert("not cell", v->tag == _CELL);

	mu_assert("NOT FOO AS LIST-CAR", strcmp(v->car->sym, "FOO") == 0);
	mu_assert("NOT BAR AS LIST-CADR", strcmp(v->cdr->car->sym, "BAR") == 0);
	mu_assert("NOT BAZ AS LIST-CADDR", strcmp(v->cdr->cdr->car->sym, "BAZ") == 0);

	// res = v->cdr->tag == _SYM;
	// mu_assert("cdr not symbol", res);
}

static char* all_tests() {
	mu_run_test(test_read_string_from_input);
	mu_run_test(test_read_symbol);
	mu_run_test(test_read_expr);  // dotted
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
