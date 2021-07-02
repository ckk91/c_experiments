#include <stdio.h>
#include <string.h>

#include "minunit.h"
#include "../src/reader.h"
#include "../src/printer.h"

int tests_run = 0;

static char* test_read_string_from_input(){
	char buffer[] = "hello";
	FILE *fstream = fmemopen(buffer, strlen(buffer), "r");

	struct stream *s = test_read_string_from_input(fstream);

	fclose(fstream);
	
	char result[6] = "";  // needs NULL
	int i= 0;
	while (s->curr->car != NULL)
	{
		result[i] = car(s->curr)->i;
		s->curr = cdr(s->curr);
		i++;
	}
	
	mu_assert("stream read mismatch", strcmp(result, buffer) == 0);
	
}

static struct stream* make_stream(char *c) {
	FILE *fstream = fmemopen(c, strlen(c), "r");

	struct stream* s = read_stream(fstream, 0);
	fclose(fstream);

    return s;
}

static char* test_read_symbol() {
	struct stream* s = make_stream("SYMBOL FOO");

	value *v = read_symbol(s);

	mu_assert("foo", v->tag == _SYM);
	mu_assert("string is not SYMBOL", strcmp(v->sym, "SYMBOL") == 0);
	// TODO test for internment
}

static char* test_read_expr() {
	struct stream* s = make_stream("(FOO BAR BAZ)");
	
	int LEN = 2;  // 3 in total

	value *v = read_expr(s);

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
	

	// res = v->cdr->tag == _SYM;
	// mu_assert("cdr not symbol", res);
}

static char* all_tests() {
	mu_run_test(test_read_stream);
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
