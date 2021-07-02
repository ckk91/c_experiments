#include "minunit.h"
#include <string.h>
#include "../src/reader.h"
#include "../src/vm.h"
#include "../src/types.h"
#include <stdlib.h>


int tests_run = 0;


// vm opstack has atoms, lists
static char* test_nil() {
	VM* vm = vm_init();
	vm->frame->c->arr[0] = make_list_field_op(vm->frame->c, NIL);
	vm->frame->c->arr[1] = make_list_field_op(vm->frame->c, STOP);
	run_vm(vm);
	mu_assert("NIL FAILED", vm_peek(vm->frame->s,0)->v == vm->NIL_CELL);

	free(vm);
}
static char* test_loadc() {
	VM* vm = vm_init();
	vm->frame->c->arr[0] = make_list_field_op(vm->frame->c, LOADC);
	vm->frame->c->arr[1] = make_list_field_op(vm->frame->c, 1);
	vm->frame->c->arr[2] = make_list_field_op(vm->frame->c, STOP);
	run_vm(vm);
	value* v = vm_peek(vm->frame->s, 0)->v;
	if(!(v->tag == _INT)) {
		return "INT";
	}
	if (!(v->i == 1)){
	 return "FOO"; 	
	}
	
	mu_assert("LOADC FAILED", v->i == 1);
	free(vm);
}
static char* test_cons() {
	VM* vm = vm_init();
	vm->frame->c->arr[0] = make_list_field_op(vm->frame->c, NIL);
	vm->frame->c->arr[1] = make_list_field_op(vm->frame->c, LOADC);
	vm->frame->c->arr[2] = make_list_field_op(vm->frame->c, 1);
	vm->frame->c->arr[3] = make_list_field_op(vm->frame->c, CONS);
	vm->frame->c->arr[4] = make_list_field_op(vm->frame->c, STOP);
	run_vm(vm);
	value* v = vm_peek(vm->frame->s, 0)->v;
	
	mu_assert("CONS NOT CELL", v->tag == _CELL);
	mu_assert("CAR NOT 1", v->car->i == 1);
	mu_assert("CDR NOT NILCELL", v->cdr == vm->NIL_CELL);
	free(vm);
}
static char* test_cons_multiple() {
	VM* vm = vm_init();
	vm->frame->c->arr[0] = make_list_field_op(vm->frame->c, NIL);
	vm->frame->c->arr[1] = make_list_field_op(vm->frame->c, LOADC);
	vm->frame->c->arr[2] = make_list_field_op(vm->frame->c, 2);
	vm->frame->c->arr[3] = make_list_field_op(vm->frame->c, CONS);
	vm->frame->c->arr[4] = make_list_field_op(vm->frame->c, LOADC);
	vm->frame->c->arr[5] = make_list_field_op(vm->frame->c, 1);
	vm->frame->c->arr[6] = make_list_field_op(vm->frame->c, CONS);
	vm->frame->c->arr[7] = make_list_field_op(vm->frame->c, STOP);
	run_vm(vm);
	value* v = vm_peek(vm->frame->s, 0)->v;
	
	mu_assert("CONS NOT CELL", v->tag == _CELL);
	mu_assert("CAR NOT 1", v->car->i == 1);
	mu_assert("CADR NOT 2", v->cdr->car->i == 2);
	mu_assert("CDDR NOT NILCELL", v->cdr->cdr == vm->NIL_CELL);
	free(vm);
}
static char* test_load_var() {
	VM* vm = vm_init();
	vm->frame->c->arr[0] = make_list_field_op(vm->frame->c, NIL);
	vm->frame->c->arr[1] = make_list_field_op(vm->frame->c, LOADC);
	vm->frame->c->arr[2] = make_list_field_op(vm->frame->c, 2);
	vm->frame->c->arr[3] = make_list_field_op(vm->frame->c, CONS);
	vm->frame->c->arr[4] = make_list_field_op(vm->frame->c, LOADC);
	vm->frame->c->arr[5] = make_list_field_op(vm->frame->c, 1);
	vm->frame->c->arr[6] = make_list_field_op(vm->frame->c, CONS);
	vm->frame->c->arr[7] = make_list_field_op(vm->frame->c, STOP);
	run_vm(vm);
	value* v = vm_peek(vm->frame->s, 0)->v;
	
	mu_assert("CONS NOT CELL", v->tag == _CELL);
	mu_assert("CAR NOT 1", v->car->i == 1);
	mu_assert("CADR NOT 2", v->cdr->car->i == 2);
	mu_assert("CDDR NOT NILCELL", v->cdr->cdr == vm->NIL_CELL);
	free(vm);

}
// static char* test_cons() {
// 	VM vm = {.c={NIL, LOADC, 1, CONS}};
// 	run_vm(&vm);
// }
// static char* test_stop;


static char* all_tests() {
	mu_run_test(test_loadc);
	mu_run_test(test_nil);
	mu_run_test(test_cons);
	mu_run_test(test_cons_multiple);
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