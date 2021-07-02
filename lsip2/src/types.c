#include "types.h"
#include <stdlib.h>
#include <string.h>
#include "globals.h"

value* make_int(int i) {
    value* rval = (value*)malloc(sizeof(value));
    rval->tag = _INT;
    rval->i = i;
    return rval;
}

value* make_lam(value *args, value *body) {
    value *c = (value*)malloc(sizeof(value));
    c->car = args;
    c->cdr = body;
    c->tag = _LAM;
    return c;    
}

value* intern(char* sym) {  // lookup
    if (SYML.car == NULL)
    {
        return 0;
    }
    
    for (value* curr = SYML.car; curr->cdr != NULL; curr = curr->cdr)  // wtf
    {
        if (strcmp(sym, curr->car->sym) == 0)
        {
            return curr->car;  // symbol in cell-car
        }
    }
    return 0;
}

value* make_sym(char* sym) {
    char* tmp = (char *)malloc(strlen(sym));  // lol, memleak
    strcpy(tmp, sym);

    // interning (a (b NIL)) cell->car
    value* foo = intern(sym);
    if (foo != 0)
    {
        return foo;
    }
        
    value* rval = (value*)malloc(sizeof(value));
    rval->tag = _SYM;
    rval->sym = tmp;
    SYML.car = cons(rval, SYML.car);

    return rval;
}

value* cons(value *car, value *cdr) {
    value *c = (value*)malloc(sizeof(value));
    c->car = car;
    c->cdr = cdr;
    c->tag = _CELL;
    return c;
}

value* v_alloc() {
    return (value*)malloc(sizeof(value));
}