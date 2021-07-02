#include "types.h"
#include <stdlib.h>
#include <stdio.h>
void print(value* v) {
    switch (v->tag)
    {
    case _CELL:
        printf("(");
        if (v->car != NULL)  // unsatisfacotry
        {
            print(v->car);
        }
        
        if (v->cdr != NULL) { 
            if (v->cdr->tag != _CELL) {
                printf(" . ");
            }
            else {

                printf(" ");
            }
            print(v->cdr); 
        }
        printf(")");
        break;
    case _INT:
        printf("%i", v->i);
        break;
    case _SYM:
        printf("%s", v->sym);
        break;
    case _FUN:
        printf("<BUILTIN @%p>", v->fn);
        break;
    default:
        printf("<NO_REPR>");
        break;
    }
}
